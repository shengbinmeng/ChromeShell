LOCAL_PATH := $(call my-dir)

#
# Prebuilt Shared library
#
include $(CLEAR_VARS)
LOCAL_MODULE	:= chromeshell
LOCAL_SRC_FILES	:= ../chromeshell/lib/$(TARGET_ARCH_ABI)/libchromeshell.so
include $(PREBUILT_SHARED_LIBRARY)
