LOCAL_PATH := $(call my-dir)

#
# Prebuilt Shared library
#
include $(CLEAR_VARS)
LOCAL_MODULE	:= chromium_android_linker
LOCAL_SRC_FILES	:= ../chromium_android_linker/lib/$(TARGET_ARCH_ABI)/libchromium_android_linker.so
include $(PREBUILT_SHARED_LIBRARY)
