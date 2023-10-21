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

# Create screen
screen = lv.obj()
screen.set_size(320, 240)
# Set style for screen, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen.set_style_bg_img_src("B:MicroPython/_nichijoubg_320x240.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
screen.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_timer
screen_cont_timer = lv.obj(screen)
screen_cont_timer.set_pos(5, 5)
screen_cont_timer.set_size(190, 200)
screen_cont_timer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_timer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_timer.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_radius(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_bg_opa(116, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_bg_color(lv.color_hex(0xcefffc), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_timer.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_cont_days
screen_cont_days = lv.obj(screen_cont_timer)
screen_cont_days.set_pos(5, 50)
screen_cont_days.set_size(200, 60)
screen_cont_days.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_days, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_days.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_bg_opa(247, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_bg_color(lv.color_hex(0x74a7cd), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_days.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_text_day
screen_text_day = lv.spangroup(screen_cont_days)
screen_text_day.set_align(lv.TEXT_ALIGN.LEFT)
screen_text_day.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_text_day.set_mode(lv.SPAN_MODE.BREAK)
# create spans
screen_text_day_span = screen_text_day.new_span()
screen_text_day_span.set_text("2023年\n")
screen_text_day_span.style.set_text_color(lv.color_hex(0xaa379d))
screen_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_text_day_span = screen_text_day.new_span()
screen_text_day_span.set_text("  ")
screen_text_day_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_day_span.style.set_text_font(test_font("Abel_regular", 28))
screen_text_day_span = screen_text_day.new_span()
screen_text_day_span.set_text("星期一")
screen_text_day_span.style.set_text_color(lv.color_hex(0x15604c))
screen_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_text_day_span = screen_text_day.new_span()
screen_text_day_span.set_text("10月21日")
screen_text_day_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_day_span.style.set_text_font(test_font("simsun", 28))
screen_text_day_span = screen_text_day.new_span()
screen_text_day_span.set_text("HELLO WORLD")
screen_text_day_span.style.set_text_color(lv.color_hex(0x000000))
screen_text_day_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_day_span.style.set_text_font(test_font("Abel_regular", 12))
screen_text_day.set_pos(0, 0)
screen_text_day.set_size(199, 59)
screen_text_day.refr_mode()
# Set style for screen_text_day, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_text_day.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_day.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_time
screen_cont_time = lv.obj(screen_cont_timer)
screen_cont_time.set_pos(-20, 3)
screen_cont_time.set_size(200, 40)
screen_cont_time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_time.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_bg_opa(222, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_bg_color(lv.color_hex(0xdeb923), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_text_time
screen_text_time = lv.spangroup(screen_cont_time)
screen_text_time.set_align(lv.TEXT_ALIGN.LEFT)
screen_text_time.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_text_time.set_mode(lv.SPAN_MODE.BREAK)
# create spans
screen_text_time_span = screen_text_time.new_span()
screen_text_time_span.set_text("00")
screen_text_time_span.style.set_text_color(lv.color_hex(0xaa379d))
screen_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_time_span.style.set_text_font(test_font("Abel_regular", 40))
screen_text_time_span = screen_text_time.new_span()
screen_text_time_span.set_text(":")
screen_text_time_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_time_span.style.set_text_font(test_font("Abel_regular", 40))
screen_text_time_span = screen_text_time.new_span()
screen_text_time_span.set_text("00")
screen_text_time_span.style.set_text_color(lv.color_hex(0x26B08C))
screen_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_time_span.style.set_text_font(test_font("Abel_regular", 40))
screen_text_time_span = screen_text_time.new_span()
screen_text_time_span.set_text(":")
screen_text_time_span.style.set_text_color(lv.color_hex(0x2F35DA))
screen_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_time_span.style.set_text_font(test_font("Abel_regular", 28))
screen_text_time_span = screen_text_time.new_span()
screen_text_time_span.set_text("00")
screen_text_time_span.style.set_text_color(lv.color_hex(0x000000))
screen_text_time_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_time_span.style.set_text_font(test_font("Abel_regular", 28))
screen_text_time.set_pos(30, 0)
screen_text_time.set_size(200, 40)
screen_text_time.refr_mode()
# Set style for screen_text_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_text_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_nichijou
screen_cont_nichijou = lv.obj(screen_cont_timer)
screen_cont_nichijou.set_pos(3, 120)
screen_cont_nichijou.set_size(180, 30)
screen_cont_nichijou.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_nichijou, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_nichijou.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_bg_opa(197, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_bg_color(lv.color_hex(0x8ce45d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_nichijou.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_text_nichijou
screen_text_nichijou = lv.spangroup(screen_cont_nichijou)
screen_text_nichijou.set_align(lv.TEXT_ALIGN.LEFT)
screen_text_nichijou.set_overflow(lv.SPAN_OVERFLOW.CLIP)
screen_text_nichijou.set_mode(lv.SPAN_MODE.BREAK)
# create spans
screen_text_nichijou_span = screen_text_nichijou.new_span()
screen_text_nichijou_span.set_text("日常NICHIJOU")
screen_text_nichijou_span.style.set_text_color(lv.color_hex(0x812a77))
screen_text_nichijou_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
screen_text_nichijou_span.style.set_text_font(test_font("simsun", 28))
screen_text_nichijou.set_pos(4, 0)
screen_text_nichijou.set_size(172, 28)
screen_text_nichijou.refr_mode()
# Set style for screen_text_nichijou, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_text_nichijou.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_text_nichijou.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_cont_weather
screen_cont_weather = lv.obj(screen)
screen_cont_weather.set_pos(200, 5)
screen_cont_weather.set_size(110, 200)
screen_cont_weather.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_cont_weather, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_cont_weather.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_border_side(lv.BORDER_SIDE.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_radius(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_bg_opa(116, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_bg_color(lv.color_hex(0xcefffc), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_cont_weather.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_label_1
screen_label_1 = lv.label(screen)
screen_label_1.set_text("我们所经历的每一个日常都是不断发生的奇迹")
screen_label_1.set_long_mode(lv.label.LONG.SCROLL_CIRCULAR)
screen_label_1.set_pos(5, 210)
screen_label_1.set_size(310, 29)
# Set style for screen_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_label_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_border_color(lv.color_hex(0x6bb8c0), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_font(test_font("simsun", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_bg_opa(185, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_bg_color(lv.color_hex(0x92bfed), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen.update_layout()

def screen_event_handler(e):
    code = e.get_code()

screen.add_event_cb(lambda e: screen_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)

