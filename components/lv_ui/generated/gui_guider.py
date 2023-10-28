# Copyright 2023 NXP
# NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=320,h=240)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(320*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 320
disp_drv.ver_res = 240
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create screen_main
screen_main = lv.obj()
screen_main.set_size(320, 240)
# Set style for screen_main, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_bg_color(lv.color_hex(0x26B08C), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_cont_timer
screen_main_cont_timer = lv.obj(screen_main)
screen_main_cont_timer.set_pos(10, 5)
screen_main_cont_timer.set_size(185, 120)
screen_main_cont_timer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_cont_timer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_timer.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_radius(7, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_bg_opa(116, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_bg_color(lv.color_hex(0xcefffc), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_timer.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_cont_days
screen_main_cont_days = lv.obj(screen_main_cont_timer)
screen_main_cont_days.set_pos(5, 56)
screen_main_cont_days.set_size(200, 60)
screen_main_cont_days.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_cont_days, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_days.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_radius(12, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_bg_opa(83, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_bg_color(lv.color_hex(0xf52cc3), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_days.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_text_day
screen_main_text_day = lv.spangroup(screen_main_cont_days)
screen_main_text_day.set_align(lv.TEXT_ALIGN.LEFT)
screen_main_text_day.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_main_text_day.set_mode(lv.SPAN_MODE.BREAK)
# create spans
screen_main_text_day_span = screen_main_text_day.new_span()
screen_main_text_day_span.set_text("2023年\n")
screen_main_text_day_span.style.set_text_color(lv.color_hex(0xaa379d))
screen_main_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_main_text_day_span = screen_main_text_day.new_span()
screen_main_text_day_span.set_text("  ")
screen_main_text_day_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_main_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_day_span.style.set_text_font(test_font("Abel_regular", 28))
screen_main_text_day_span = screen_main_text_day.new_span()
screen_main_text_day_span.set_text("星期一")
screen_main_text_day_span.style.set_text_color(lv.color_hex(0x15604c))
screen_main_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_main_text_day_span = screen_main_text_day.new_span()
screen_main_text_day_span.set_text("10月21日")
screen_main_text_day_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_main_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_main_text_day_span = screen_main_text_day.new_span()
screen_main_text_day_span.set_text(" HUST")
screen_main_text_day_span.style.set_text_color(lv.color_hex(0x343434))
screen_main_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_day_span.style.set_text_font(test_font("YournameD7CentralNarrow", 28))
screen_main_text_day.set_pos(-3, 1)
screen_main_text_day.set_size(181, 59)
screen_main_text_day.refr_mode()
# Set style for screen_main_text_day, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_text_day.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_day.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_cont_time
screen_main_cont_time = lv.obj(screen_main_cont_timer)
screen_main_cont_time.set_pos(-20, -1)
screen_main_cont_time.set_size(200, 40)
screen_main_cont_time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_cont_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_time.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_radius(12, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_bg_opa(110, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_bg_color(lv.color_hex(0x134aa8), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_text_time
screen_main_text_time = lv.spangroup(screen_main_cont_time)
screen_main_text_time.set_align(lv.TEXT_ALIGN.LEFT)
screen_main_text_time.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_main_text_time.set_mode(lv.SPAN_MODE.BREAK)
# create spans
screen_main_text_time_span = screen_main_text_time.new_span()
screen_main_text_time_span.set_text("00")
screen_main_text_time_span.style.set_text_color(lv.color_hex(0xaa379d))
screen_main_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_time_span.style.set_text_font(test_font("YournameD7CentralNarrow", 40))
screen_main_text_time_span = screen_main_text_time.new_span()
screen_main_text_time_span.set_text(":")
screen_main_text_time_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_main_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_time_span.style.set_text_font(test_font("YournameD7CentralNarrow", 40))
screen_main_text_time_span = screen_main_text_time.new_span()
screen_main_text_time_span.set_text("00")
screen_main_text_time_span.style.set_text_color(lv.color_hex(0xff6500))
screen_main_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_time_span.style.set_text_font(test_font("YournameD7CentralNarrow", 40))
screen_main_text_time_span = screen_main_text_time.new_span()
screen_main_text_time_span.set_text(":")
screen_main_text_time_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_main_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_time_span.style.set_text_font(test_font("YournameD7CentralNarrow", 28))
screen_main_text_time_span = screen_main_text_time.new_span()
screen_main_text_time_span.set_text("00")
screen_main_text_time_span.style.set_text_color(lv.color_hex(0x000000))
screen_main_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_main_text_time_span.style.set_text_font(test_font("YournameD7CentralNarrow", 28))
screen_main_text_time.set_pos(31, -2)
screen_main_text_time.set_size(200, 40)
screen_main_text_time.refr_mode()
# Set style for screen_main_text_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_text_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_text_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_cont_weather
screen_main_cont_weather = lv.obj(screen_main)
screen_main_cont_weather.set_pos(200, 5)
screen_main_cont_weather.set_size(110, 120)
screen_main_cont_weather.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_cont_weather.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_main_cont_weather, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_weather.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_radius(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_bg_opa(116, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_bg_color(lv.color_hex(0xcefffc), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_weather.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_list_weatehr
screen_main_list_weatehr = lv.list(screen_main_cont_weather)
screen_main_list_weatehr_item0 = screen_main_list_weatehr.add_btn("B:MicroPython/_5729377_forecast_windy_weather_storm_climate_alpha_64x64.bin", "windy")
screen_main_list_weatehr_item1 = screen_main_list_weatehr.add_btn("B:MicroPython/_5729383_forecast_rain_cloud_weather_raining_alpha_64x64.bin", "rain")
screen_main_list_weatehr_item2 = screen_main_list_weatehr.add_btn("B:MicroPython/_5729378_sunny_sun_weather_climate_forecast_alpha_64x64.bin", "sun")
screen_main_list_weatehr_item3 = screen_main_list_weatehr.add_btn("B:MicroPython/_5729385_forecast_moon_weather_night_crescent_climate_alpha_64x64.bin", "moon")
screen_main_list_weatehr.set_pos(40, 5)
screen_main_list_weatehr.set_size(64, 64)
screen_main_list_weatehr.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_list_weatehr, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_list_weatehr.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_list_weatehr, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_main_list_weatehr.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_weatehr.set_style_bg_opa(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_main_list_weatehr, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_weatehr_extra_btns_main_default = lv.style_t()
style_screen_main_list_weatehr_extra_btns_main_default.init()
style_screen_main_list_weatehr_extra_btns_main_default.set_pad_top(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_pad_left(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_pad_right(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_pad_bottom(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_border_width(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_main_list_weatehr_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_main_list_weatehr_extra_btns_main_default.set_radius(0)
style_screen_main_list_weatehr_extra_btns_main_default.set_bg_opa(0)
screen_main_list_weatehr_item3.add_style(style_screen_main_list_weatehr_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr_item2.add_style(style_screen_main_list_weatehr_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr_item1.add_style(style_screen_main_list_weatehr_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_weatehr_item0.add_style(style_screen_main_list_weatehr_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_list_weatehr, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_weatehr_extra_texts_main_default = lv.style_t()
style_screen_main_list_weatehr_extra_texts_main_default.init()
style_screen_main_list_weatehr_extra_texts_main_default.set_pad_top(0)
style_screen_main_list_weatehr_extra_texts_main_default.set_pad_left(0)
style_screen_main_list_weatehr_extra_texts_main_default.set_pad_right(0)
style_screen_main_list_weatehr_extra_texts_main_default.set_pad_bottom(0)
style_screen_main_list_weatehr_extra_texts_main_default.set_border_width(0)
style_screen_main_list_weatehr_extra_texts_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_main_list_weatehr_extra_texts_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_main_list_weatehr_extra_texts_main_default.set_radius(3)
style_screen_main_list_weatehr_extra_texts_main_default.set_bg_opa(0)

# Create screen_main_label_2
screen_main_label_2 = lv.label(screen_main_cont_weather)
screen_main_label_2.set_text("刮风")
screen_main_label_2.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_2.set_pos(-4, 25)
screen_main_label_2.set_size(60, 24)
# Set style for screen_main_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_text_color(lv.color_hex(0x480a92), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_text_font(test_font("simsun", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_chart_temp
screen_main_chart_temp = lv.chart(screen_main_cont_weather)
screen_main_chart_temp.set_type(lv.chart.TYPE.BAR)
screen_main_chart_temp.set_div_line_count(0, 0)
screen_main_chart_temp.set_point_count(2)
screen_main_chart_temp.set_range(lv.chart.AXIS.PRIMARY_Y, 0, 40)
screen_main_chart_temp.set_range(lv.chart.AXIS.SECONDARY_Y, 0, 2)
screen_main_chart_temp.set_zoom_x(256)
screen_main_chart_temp.set_zoom_y(256)
screen_main_chart_temp_series_0 = screen_main_chart_temp.add_series(lv.color_hex(0x8d666c), lv.chart.AXIS.PRIMARY_Y)
screen_main_chart_temp.set_next_value(screen_main_chart_temp_series_0, 12)
screen_main_chart_temp.set_next_value(screen_main_chart_temp_series_0, 28)
screen_main_chart_temp.set_pos(5, 44)
screen_main_chart_temp.set_size(75, 61)
screen_main_chart_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_chart_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_chart_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_color(lv.color_hex(0xe73131), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_opa(176, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_chart_temp, Part: lv.PART.TICKS, State: lv.STATE.DEFAULT.
screen_main_chart_temp.set_style_text_color(lv.color_hex(0x5a2424), lv.PART.TICKS|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_text_font(test_font("montserratMedium", 12), lv.PART.TICKS|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_width(2, lv.PART.TICKS|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_color(lv.color_hex(0x8f2020), lv.PART.TICKS|lv.STATE.DEFAULT)
screen_main_chart_temp.set_style_line_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)

# Create screen_main_label_3
screen_main_label_3 = lv.label(screen_main_cont_weather)
screen_main_label_3.set_text("Temp")
screen_main_label_3.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_3.set_pos(68, 76)
screen_main_label_3.set_size(45, 16)
# Set style for screen_main_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_text_color(lv.color_hex(0x990303), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_4
screen_main_label_4 = lv.label(screen_main_cont_weather)
screen_main_label_4.set_text("12")
screen_main_label_4.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_4.set_pos(14, 105)
screen_main_label_4.set_size(18, 15)
# Set style for screen_main_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_text_color(lv.color_hex(0x626262), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_temp_high
screen_main_label_temp_high = lv.label(screen_main_cont_weather)
screen_main_label_temp_high.set_text("28")
screen_main_label_temp_high.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_temp_high.set_pos(52, 105)
screen_main_label_temp_high.set_size(18, 15)
# Set style for screen_main_label_temp_high, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_temp_high.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_text_color(lv.color_hex(0x5c5c5c), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_temp_high.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_nichijou
screen_main_label_nichijou = lv.label(screen_main)
screen_main_label_nichijou.set_text("我们所经历的每一个日常，也许都是不断发生的奇迹！")
screen_main_label_nichijou.set_long_mode(lv.label.LONG.SCROLL_CIRCULAR)
screen_main_label_nichijou.set_pos(10, 208)
screen_main_label_nichijou.set_size(300, 29)
# Set style for screen_main_label_nichijou, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_nichijou.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_border_color(lv.color_hex(0x6bb8c0), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_text_color(lv.color_hex(0x595959), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_text_font(test_font("simsun", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_bg_opa(110, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_nichijou.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_cont_music
screen_main_cont_music = lv.obj(screen_main)
screen_main_cont_music.set_pos(10, 130)
screen_main_cont_music.set_size(300, 74)
screen_main_cont_music.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_cont_music, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_music.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_bg_opa(104, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_music.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_img_music
screen_main_img_music = lv.img(screen_main_cont_music)
screen_main_img_music.set_src("B:MicroPython/_music2_alpha_70x70.bin")
screen_main_img_music.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_music.set_pivot(50,50)
screen_main_img_music.set_angle(0)
screen_main_img_music.set_pos(10, 0)
screen_main_img_music.set_size(70, 70)
# Set style for screen_main_img_music, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_music.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_line_1
screen_main_line_1 = lv.line(screen_main_cont_music)
screen_main_line_1_line_points = [{"x":0, "y":0},{"x":0, "y":60},]
screen_main_line_1.set_points(screen_main_line_1_line_points, 2)
screen_main_line_1.set_pos(90, 5)
screen_main_line_1.set_size(6, 60)
# Set style for screen_main_line_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_line_1.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_line_1.set_style_line_color(lv.color_hex(0x14b319), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_line_1.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_line_1.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_play_last
screen_main_img_play_last = lv.img(screen_main_cont_music)
screen_main_img_play_last.set_src("B:MicroPython/_play_last_alpha_15x15.bin")
screen_main_img_play_last.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_play_last.set_pivot(0,0)
screen_main_img_play_last.set_angle(0)
screen_main_img_play_last.set_pos(151, 51)
screen_main_img_play_last.set_size(15, 15)
# Set style for screen_main_img_play_last, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_play_last.set_style_img_recolor_opa(235, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play_last.set_style_img_recolor(lv.color_hex(0x246700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play_last.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_play_next
screen_main_img_play_next = lv.img(screen_main_cont_music)
screen_main_img_play_next.set_src("B:MicroPython/_play_next_alpha_15x15.bin")
screen_main_img_play_next.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_play_next.set_pivot(0,0)
screen_main_img_play_next.set_angle(0)
screen_main_img_play_next.set_pos(217, 51)
screen_main_img_play_next.set_size(15, 15)
# Set style for screen_main_img_play_next, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_play_next.set_style_img_recolor_opa(235, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play_next.set_style_img_recolor(lv.color_hex(0x246700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play_next.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_play
screen_main_img_play = lv.img(screen_main_cont_music)
screen_main_img_play.set_src("B:MicroPython/_play_alpha_15x15.bin")
screen_main_img_play.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_play.set_pivot(8,8)
screen_main_img_play.set_angle(0)
screen_main_img_play.set_pos(184, 51)
screen_main_img_play.set_size(15, 15)
# Set style for screen_main_img_play, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_play.set_style_img_recolor_opa(235, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play.set_style_img_recolor(lv.color_hex(0x246700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_play.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_love
screen_main_img_love = lv.img(screen_main_cont_music)
screen_main_img_love.set_src("B:MicroPython/_love_alpha_15x15.bin")
screen_main_img_love.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_love.set_pivot(0,0)
screen_main_img_love.set_angle(0)
screen_main_img_love.set_pos(103, 51)
screen_main_img_love.set_size(15, 15)
# Set style for screen_main_img_love, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_love.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_bar_play
screen_main_bar_play = lv.bar(screen_main_cont_music)
screen_main_bar_play.set_style_anim_time(1000, 0)
screen_main_bar_play.set_mode(lv.bar.MODE.NORMAL)
screen_main_bar_play.set_value(50, lv.ANIM.OFF)
screen_main_bar_play.set_pos(95, 44)
screen_main_bar_play.set_size(200, 4)
# Set style for screen_main_bar_play, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_bar_play.set_style_bg_opa(70, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_bg_color(lv.color_hex(0x007fff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_main_bar_play, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_main_bar_play.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_bg_color(lv.color_hex(0xfa6300), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_bg_grad_color(lv.color_hex(0xb70adf), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_bar_play.set_style_radius(10, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create screen_main_img_voice
screen_main_img_voice = lv.img(screen_main_cont_music)
screen_main_img_voice.set_src("B:MicroPython/_voice_alpha_15x15.bin")
screen_main_img_voice.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_voice.set_pivot(0,0)
screen_main_img_voice.set_angle(0)
screen_main_img_voice.set_pos(275, 51)
screen_main_img_voice.set_size(15, 15)
# Set style for screen_main_img_voice, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_voice.set_style_img_recolor_opa(235, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_voice.set_style_img_recolor(lv.color_hex(0x246700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_voice.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_mute
screen_main_img_mute = lv.img(screen_main_cont_music)
screen_main_img_mute.set_src("B:MicroPython/_voice_mute_alpha_15x15.bin")
screen_main_img_mute.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_mute.set_pivot(0,0)
screen_main_img_mute.set_angle(0)
screen_main_img_mute.set_pos(275, 51)
screen_main_img_mute.set_size(15, 15)
screen_main_img_mute.add_flag(lv.obj.FLAG.HIDDEN)
# Set style for screen_main_img_mute, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_mute.set_style_img_recolor_opa(235, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_mute.set_style_img_recolor(lv.color_hex(0x246700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_img_mute.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_music
screen_main_label_music = lv.label(screen_main_cont_music)
screen_main_label_music.set_text("By my side")
screen_main_label_music.set_long_mode(lv.label.LONG.SCROLL_CIRCULAR)
screen_main_label_music.set_pos(100, 10)
screen_main_label_music.set_size(125, 14)
# Set style for screen_main_label_music, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_music.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_music.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_art
screen_main_label_art = lv.label(screen_main_cont_music)
screen_main_label_art.set_text("Radwimps")
screen_main_label_art.set_long_mode(lv.label.LONG.CLIP)
screen_main_label_art.set_pos(100, 25)
screen_main_label_art.set_size(140, 14)
# Set style for screen_main_label_art, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_art.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_text_color(lv.color_hex(0x5b5b5b), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_art.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_time
screen_main_label_time = lv.label(screen_main_cont_music)
screen_main_label_time.set_text("02:00/4:50")
screen_main_label_time.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_time.set_pos(204, 25)
screen_main_label_time.set_size(90, 12)
# Set style for screen_main_label_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_text_font(test_font("Abel_regular", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_btn_app1
screen_main_btn_app1 = lv.btn(screen_main)
screen_main_btn_app1_label = lv.label(screen_main_btn_app1)
screen_main_btn_app1_label.set_text("")
screen_main_btn_app1_label.set_long_mode(lv.label.LONG.WRAP)
screen_main_btn_app1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_main_btn_app1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_app1.set_pos(310, 207)
screen_main_btn_app1.set_size(10, 30)
# Set style for screen_main_btn_app1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_btn_app1.set_style_bg_opa(58, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_bg_color(lv.color_hex(0xa50000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_app1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_menu1
screen_main_img_menu1 = lv.img(screen_main)
screen_main_img_menu1.set_src("B:MicroPython/_menu_alpha_20x20.bin")
screen_main_img_menu1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_menu1.set_pivot(50,50)
screen_main_img_menu1.set_angle(0)
screen_main_img_menu1.set_pos(300, 117)
screen_main_img_menu1.set_size(20, 20)
screen_main_img_menu1.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_main_img_menu1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_menu1.set_style_img_opa(93, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_list_musics
screen_main_list_musics = lv.list(screen_main)
screen_main_list_musics_item0 = screen_main_list_musics.add_text("Musics")
screen_main_list_musics.set_pos(247, 25)
screen_main_list_musics.set_size(73, 182)
screen_main_list_musics.add_flag(lv.obj.FLAG.HIDDEN)
screen_main_list_musics.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_list_musics, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_list_musics.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_pad_right(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_pad_bottom(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_opa(215, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_color(lv.color_hex(0xd86700), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_grad_dir(lv.GRAD_DIR.VER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_grad_color(lv.color_hex(0x35a605), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_list_musics, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_main_list_musics.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_musics.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_main_list_musics, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_musics_extra_btns_main_default = lv.style_t()
style_screen_main_list_musics_extra_btns_main_default.init()
style_screen_main_list_musics_extra_btns_main_default.set_pad_top(0)
style_screen_main_list_musics_extra_btns_main_default.set_pad_left(0)
style_screen_main_list_musics_extra_btns_main_default.set_pad_right(0)
style_screen_main_list_musics_extra_btns_main_default.set_pad_bottom(0)
style_screen_main_list_musics_extra_btns_main_default.set_border_width(0)
style_screen_main_list_musics_extra_btns_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_main_list_musics_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_main_list_musics_extra_btns_main_default.set_radius(3)
style_screen_main_list_musics_extra_btns_main_default.set_bg_opa(144)
style_screen_main_list_musics_extra_btns_main_default.set_bg_color(lv.color_hex(0x340000))

# Set style for screen_main_list_musics, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_musics_extra_texts_main_default = lv.style_t()
style_screen_main_list_musics_extra_texts_main_default.init()
style_screen_main_list_musics_extra_texts_main_default.set_pad_top(5)
style_screen_main_list_musics_extra_texts_main_default.set_pad_left(0)
style_screen_main_list_musics_extra_texts_main_default.set_pad_right(0)
style_screen_main_list_musics_extra_texts_main_default.set_pad_bottom(5)
style_screen_main_list_musics_extra_texts_main_default.set_border_width(2)
style_screen_main_list_musics_extra_texts_main_default.set_border_opa(255)
style_screen_main_list_musics_extra_texts_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_screen_main_list_musics_extra_texts_main_default.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_screen_main_list_musics_extra_texts_main_default.set_text_color(lv.color_hex(0xeaeaea))
style_screen_main_list_musics_extra_texts_main_default.set_text_font(test_font("Abel_regular", 12))
style_screen_main_list_musics_extra_texts_main_default.set_radius(2)
style_screen_main_list_musics_extra_texts_main_default.set_bg_opa(0)
screen_main_list_musics_item0.add_style(style_screen_main_list_musics_extra_texts_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_cont_app
screen_main_cont_app = lv.obj(screen_main)
screen_main_cont_app.set_pos(0, 205)
screen_main_cont_app.set_size(320, 35)
screen_main_cont_app.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_cont_app, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_cont_app.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_bg_color(lv.color_hex(0x7ab957), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_bg_grad_color(lv.color_hex(0x8c8a85), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_cont_app.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_btn_select
screen_main_btn_select = lv.btn(screen_main_cont_app)
screen_main_btn_select_label = lv.label(screen_main_btn_select)
screen_main_btn_select_label.set_text("")
screen_main_btn_select_label.set_long_mode(lv.label.LONG.WRAP)
screen_main_btn_select_label.align(lv.ALIGN.CENTER, 0, 0)
screen_main_btn_select.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_select.set_pos(3, 1)
screen_main_btn_select.set_size(35, 32)
# Set style for screen_main_btn_select, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_btn_select.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_bg_color(lv.color_hex(0x66c5ac), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_select.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_main
screen_main_img_main = lv.img(screen_main_cont_app)
screen_main_img_main.set_src("B:MicroPython/_love_alpha_30x30.bin")
screen_main_img_main.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_main.set_pivot(50,50)
screen_main_img_main.set_angle(0)
screen_main_img_main.set_pos(5, 2)
screen_main_img_main.set_size(30, 30)
# Set style for screen_main_img_main, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_main.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_img_read
screen_main_img_img_read = lv.img(screen_main_cont_app)
screen_main_img_img_read.set_src("B:MicroPython/_picture_alpha_30x30.bin")
screen_main_img_img_read.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_img_read.set_pivot(50,50)
screen_main_img_img_read.set_angle(0)
screen_main_img_img_read.set_pos(55, 2)
screen_main_img_img_read.set_size(30, 30)
# Set style for screen_main_img_img_read, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_img_read.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_reader
screen_main_img_reader = lv.img(screen_main_cont_app)
screen_main_img_reader.set_src("B:MicroPython/_reader_alpha_30x30.bin")
screen_main_img_reader.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_reader.set_pivot(50,50)
screen_main_img_reader.set_angle(0)
screen_main_img_reader.set_pos(105, 2)
screen_main_img_reader.set_size(30, 30)
# Set style for screen_main_img_reader, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_reader.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_setting
screen_main_img_setting = lv.img(screen_main_cont_app)
screen_main_img_setting.set_src("B:MicroPython/_setting1_alpha_30x30.bin")
screen_main_img_setting.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_setting.set_pivot(50,50)
screen_main_img_setting.set_angle(0)
screen_main_img_setting.set_pos(155, 2)
screen_main_img_setting.set_size(30, 30)
screen_main_img_setting.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_main_img_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_setting.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_img_light
screen_main_img_light = lv.img(screen_main_cont_app)
screen_main_img_light.set_src("B:MicroPython/_nichijoubg_alpha_30x30.bin")
screen_main_img_light.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_light.set_pivot(50,50)
screen_main_img_light.set_angle(0)
screen_main_img_light.set_pos(205, 3)
screen_main_img_light.set_size(30, 30)
screen_main_img_light.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_main_img_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_light.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_slider_light
screen_main_slider_light = lv.slider(screen_main)
screen_main_slider_light.set_range(0, 100)
screen_main_slider_light.set_mode(lv.slider.MODE.NORMAL)
screen_main_slider_light.set_value(50, lv.ANIM.OFF)
screen_main_slider_light.set_pos(43, 104)
screen_main_slider_light.set_size(234, 46)
screen_main_slider_light.add_flag(lv.obj.FLAG.HIDDEN)
# Set style for screen_main_slider_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_slider_light.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_outline_width(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_outline_opa(216, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_outline_color(lv.color_hex(0xcecece), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_slider_light, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_main_slider_light.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_color(lv.color_hex(0xb8b84b), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_grad_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_main_slider_light, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_main_slider_light.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_img_src("B:MicroPython/_nichijoubg_52x52.bin", lv.PART.KNOB|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_bg_img_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_main_slider_light.set_style_radius(50, lv.PART.KNOB|lv.STATE.DEFAULT)

screen_main.update_layout()
# Create screen_setting
screen_setting = lv.obj()
screen_setting.set_size(320, 240)
# Set style for screen_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_setting_tileview_setting
screen_setting_tileview_setting = lv.tileview(screen_setting)
screen_setting_tileview_setting_tile_main = screen_setting_tileview_setting.add_tile(0, 0, lv.DIR.BOTTOM)
screen_setting_tileview_setting_tile_wifi = screen_setting_tileview_setting.add_tile(0, 1, lv.DIR.TOP | lv.DIR.BOTTOM)
screen_setting_tileview_setting_tile_ble = screen_setting_tileview_setting.add_tile(0, 2, lv.DIR.TOP | lv.DIR.BOTTOM)
screen_setting_tileview_setting_tile_uart = screen_setting_tileview_setting.add_tile(0, 3, lv.DIR.TOP)
screen_setting_tileview_setting.set_pos(25, 20)
screen_setting_tileview_setting.set_size(280, 200)
screen_setting_tileview_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.AUTO)
# Set style for screen_setting_tileview_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting_tileview_setting.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_tileview_setting.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_tileview_setting.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_setting_tileview_setting, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_setting_tileview_setting.set_style_bg_opa(226, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_setting_tileview_setting.set_style_bg_color(lv.color_hex(0xea7c00), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_setting_tileview_setting.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_setting_list_setting
screen_setting_list_setting = lv.list(screen_setting_tileview_setting_tile_main)
screen_setting_list_setting_item0 = screen_setting_list_setting.add_btn("B:MicroPython/_wifi1_alpha_20x20.bin", "WIFI")
screen_setting_list_setting_item1 = screen_setting_list_setting.add_btn("B:MicroPython/_bluetooth30_30_alpha_20x20.bin", "BLE")
screen_setting_list_setting_item2 = screen_setting_list_setting.add_btn("B:MicroPython/_api_alpha_20x20.bin", "COM")
screen_setting_list_setting.set_pos(0, 0)
screen_setting_list_setting.set_size(265, 200)
screen_setting_list_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_setting_list_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting_list_setting.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_border_opa(135, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_border_color(lv.color_hex(0x087544), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_border_side(lv.BORDER_SIDE.TOP | lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_setting_list_setting, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_setting_list_setting.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_setting_list_setting.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_setting_list_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_setting_list_setting_extra_btns_main_default = lv.style_t()
style_screen_setting_list_setting_extra_btns_main_default.init()
style_screen_setting_list_setting_extra_btns_main_default.set_pad_top(10)
style_screen_setting_list_setting_extra_btns_main_default.set_pad_left(5)
style_screen_setting_list_setting_extra_btns_main_default.set_pad_right(5)
style_screen_setting_list_setting_extra_btns_main_default.set_pad_bottom(5)
style_screen_setting_list_setting_extra_btns_main_default.set_border_width(0)
style_screen_setting_list_setting_extra_btns_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_setting_list_setting_extra_btns_main_default.set_text_font(test_font("Abel_regular", 12))
style_screen_setting_list_setting_extra_btns_main_default.set_radius(0)
style_screen_setting_list_setting_extra_btns_main_default.set_bg_opa(44)
style_screen_setting_list_setting_extra_btns_main_default.set_bg_color(lv.color_hex(0xd04545))
screen_setting_list_setting_item2.add_style(style_screen_setting_list_setting_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting_item1.add_style(style_screen_setting_list_setting_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_setting_list_setting_item0.add_style(style_screen_setting_list_setting_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_setting_list_setting, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
style_screen_setting_list_setting_extra_btns_main_pressed = lv.style_t()
style_screen_setting_list_setting_extra_btns_main_pressed.init()
style_screen_setting_list_setting_extra_btns_main_pressed.set_pad_top(5)
style_screen_setting_list_setting_extra_btns_main_pressed.set_pad_left(5)
style_screen_setting_list_setting_extra_btns_main_pressed.set_pad_right(5)
style_screen_setting_list_setting_extra_btns_main_pressed.set_pad_bottom(5)
style_screen_setting_list_setting_extra_btns_main_pressed.set_border_width(0)
style_screen_setting_list_setting_extra_btns_main_pressed.set_radius(3)
style_screen_setting_list_setting_extra_btns_main_pressed.set_text_color(lv.color_hex(0x0D3055))
style_screen_setting_list_setting_extra_btns_main_pressed.set_text_font(test_font("Abel_regular", 12))
style_screen_setting_list_setting_extra_btns_main_pressed.set_bg_opa(88)
style_screen_setting_list_setting_extra_btns_main_pressed.set_bg_color(lv.color_hex(0x29ff00))
screen_setting_list_setting_item2.add_style(style_screen_setting_list_setting_extra_btns_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)
screen_setting_list_setting_item1.add_style(style_screen_setting_list_setting_extra_btns_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)
screen_setting_list_setting_item0.add_style(style_screen_setting_list_setting_extra_btns_main_pressed, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_setting_list_setting, Part: lv.PART.MAIN, State: lv.STATE.FOCUSED.
style_screen_setting_list_setting_extra_btns_main_focused = lv.style_t()
style_screen_setting_list_setting_extra_btns_main_focused.init()
style_screen_setting_list_setting_extra_btns_main_focused.set_pad_top(5)
style_screen_setting_list_setting_extra_btns_main_focused.set_pad_left(5)
style_screen_setting_list_setting_extra_btns_main_focused.set_pad_right(5)
style_screen_setting_list_setting_extra_btns_main_focused.set_pad_bottom(5)
style_screen_setting_list_setting_extra_btns_main_focused.set_border_width(5)
style_screen_setting_list_setting_extra_btns_main_focused.set_border_opa(255)
style_screen_setting_list_setting_extra_btns_main_focused.set_border_color(lv.color_hex(0xffffff))
style_screen_setting_list_setting_extra_btns_main_focused.set_border_side(lv.BORDER_SIDE.FULL)
style_screen_setting_list_setting_extra_btns_main_focused.set_radius(3)
style_screen_setting_list_setting_extra_btns_main_focused.set_text_color(lv.color_hex(0x0D3055))
style_screen_setting_list_setting_extra_btns_main_focused.set_text_font(test_font("Abel_regular", 12))
style_screen_setting_list_setting_extra_btns_main_focused.set_bg_opa(255)
style_screen_setting_list_setting_extra_btns_main_focused.set_bg_color(lv.color_hex(0x55acaa))
screen_setting_list_setting_item2.add_style(style_screen_setting_list_setting_extra_btns_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)
screen_setting_list_setting_item1.add_style(style_screen_setting_list_setting_extra_btns_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)
screen_setting_list_setting_item0.add_style(style_screen_setting_list_setting_extra_btns_main_focused, lv.PART.MAIN|lv.STATE.FOCUSED)
# Set style for screen_setting_list_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_setting_list_setting_extra_texts_main_default = lv.style_t()
style_screen_setting_list_setting_extra_texts_main_default.init()
style_screen_setting_list_setting_extra_texts_main_default.set_pad_top(5)
style_screen_setting_list_setting_extra_texts_main_default.set_pad_left(5)
style_screen_setting_list_setting_extra_texts_main_default.set_pad_right(5)
style_screen_setting_list_setting_extra_texts_main_default.set_pad_bottom(5)
style_screen_setting_list_setting_extra_texts_main_default.set_border_width(0)
style_screen_setting_list_setting_extra_texts_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_setting_list_setting_extra_texts_main_default.set_text_font(test_font("Abel_regular", 12))
style_screen_setting_list_setting_extra_texts_main_default.set_radius(3)
style_screen_setting_list_setting_extra_texts_main_default.set_bg_opa(161)
style_screen_setting_list_setting_extra_texts_main_default.set_bg_color(lv.color_hex(0xffffff))

# Create screen_setting_img_menu2
screen_setting_img_menu2 = lv.img(screen_setting)
screen_setting_img_menu2.set_src("B:MicroPython/_menu_alpha_20x20.bin")
screen_setting_img_menu2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_setting_img_menu2.set_pivot(0,0)
screen_setting_img_menu2.set_angle(0)
screen_setting_img_menu2.set_pos(300, 135)
screen_setting_img_menu2.set_size(20, 20)
screen_setting_img_menu2.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_setting_img_menu2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting_img_menu2.set_style_img_opa(93, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_setting_img_home2
screen_setting_img_home2 = lv.img(screen_setting)
screen_setting_img_home2.set_src("B:MicroPython/_home_alpha_20x20.bin")
screen_setting_img_home2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_setting_img_home2.set_pivot(0,0)
screen_setting_img_home2.set_angle(0)
screen_setting_img_home2.set_pos(300, 220)
screen_setting_img_home2.set_size(20, 20)
screen_setting_img_home2.add_flag(lv.obj.FLAG.CLICKABLE)
# Set style for screen_setting_img_home2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_setting_img_home2.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_setting.update_layout()

def screen_main_event_handler(e):
    code = e.get_code()

screen_main.add_event_cb(lambda e: screen_main_event_handler(e), lv.EVENT.ALL, None)

def screen_main_cont_weather_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        screen_main_img_voice.add_flag(lv.obj.FLAG.HIDDEN);screen_main_img_mute.clear_flag(lv.obj.FLAG.HIDDEN)

screen_main_cont_weather.add_event_cb(lambda e: screen_main_cont_weather_event_handler(e), lv.EVENT.ALL, None)

def screen_main_btn_app1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        screen_main_cont_app.clear_flag(lv.obj.FLAG.HIDDEN);screen_main_list_musics.add_flag(lv.obj.FLAG.HIDDEN)

screen_main_btn_app1.add_event_cb(lambda e: screen_main_btn_app1_event_handler(e), lv.EVENT.ALL, None)

def screen_main_img_menu1_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        screen_main_list_musics.clear_flag(lv.obj.FLAG.HIDDEN);screen_main_cont_app.add_flag(lv.obj.FLAG.HIDDEN)

screen_main_img_menu1.add_event_cb(lambda e: screen_main_img_menu1_event_handler(e), lv.EVENT.ALL, None)

def screen_main_img_setting_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(screen_setting, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

screen_main_img_setting.add_event_cb(lambda e: screen_main_img_setting_event_handler(e), lv.EVENT.ALL, None)

def screen_main_img_light_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        screen_main_slider_light.clear_flag(lv.obj.FLAG.HIDDEN)

screen_main_img_light.add_event_cb(lambda e: screen_main_img_light_event_handler(e), lv.EVENT.ALL, None)

def screen_setting_list_setting_event_handler(e):
    code = e.get_code()

screen_setting_list_setting.add_event_cb(lambda e: screen_setting_list_setting_event_handler(e), lv.EVENT.ALL, None)

def screen_setting_img_home2_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        lv.scr_load_anim(screen_main, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)

screen_setting_img_home2.add_event_cb(lambda e: screen_setting_img_home2_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(screen_setting)

while SDL.check():
    time.sleep_ms(5)

