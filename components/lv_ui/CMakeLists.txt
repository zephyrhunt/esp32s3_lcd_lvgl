
#idf_component_register(SRC_DIRS ui/ ui/screens ui/components ui/fonts ui/images
#                       INCLUDE_DIRS ui/ ui/screens ui/components ui/fonts ui/images
#                       REQUIRES driver lvgl)

idf_component_register(SRC_DIRS generated custom  generated/guider_fonts generated/guider_customer_fonts generated/images
        INCLUDE_DIRS generated custom  generated/guider_fonts generated/guider_customer_fonts generated/images
        REQUIRES driver lvgl)
