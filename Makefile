# Makefile for C/C++, Obj-C/C++, iOS apps
#
# Written by Federico Sandri <uroboro.845@gmail.com>
# (C) 2012-2013

################################################################

PROJECTNAME = listlib

# if it's an app,
COMPANYNAME = corp

# version numbers
VERSION = 0
REVISION = 0
PATCH = 1

# options: c, cplusplus, objc, objcplusplus
LANGUAGE = c

# options:
# `terminal' for commandline programs
# `ios' for iOS apps
PLATFORM = terminal

# if language is objc, add frameworks to the list:
FRAMEWORKS = 

#CFLAGS = 
#LDFLAGS = 

include ~/code/makefiles/common.mk

