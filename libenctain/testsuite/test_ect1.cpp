// $Id$

#include "enctain.h"

#include <assert.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#define WRITEFILE	0

static char testtext[2843] = {
    0x2f,0x2f,0x20,0x24,0x49,0x64,0x3a,0x20,0x74,0x65,0x73,0x74,0x5f,0x74,0x78,0x63,
    0x2e,0x63,0x70,0x70,0x20,0x34,0x33,0x20,0x32,0x30,0x30,0x37,0x2d,0x31,0x32,0x2d,
    0x31,0x37,0x20,0x32,0x33,0x3a,0x31,0x34,0x3a,0x31,0x39,0x5a,0x20,0x74,0x62,0x20,
    0x24,0x0a,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x22,0x65,0x6e,0x63,
    0x74,0x61,0x69,0x6e,0x2e,0x68,0x22,0x0a,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,
    0x65,0x20,0x3c,0x77,0x78,0x2f,0x77,0x66,0x73,0x74,0x72,0x65,0x61,0x6d,0x2e,0x68,
    0x3e,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x3c,0x69,0x6f,0x73,0x74,
    0x72,0x65,0x61,0x6d,0x3e,0x0a,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x63,0x68,
    0x61,0x72,0x20,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x5b,0x37,0x33,0x30,0x5d,
    0x20,0x3d,0x20,0x7b,0x0a,0x7d,0x3b,0x0a,0x0a,0x69,0x6e,0x74,0x20,0x6d,0x61,0x69,
    0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x73,0x74,0x64,0x3a,0x3a,0x63,
    0x6f,0x75,0x74,0x20,0x3c,0x3c,0x20,0x22,0x54,0x65,0x73,0x74,0x69,0x6e,0x67,0x20,
    0x45,0x6e,0x63,0x72,0x79,0x70,0x74,0x65,0x64,0x20,0x43,0x6f,0x6e,0x74,0x61,0x69,
    0x6e,0x65,0x72,0x20,0x69,0x6d,0x70,0x6c,0x65,0x6d,0x65,0x6e,0x74,0x61,0x74,0x69,
    0x6f,0x6e,0x2e,0x2e,0x2e,0x22,0x3b,0x0a,0x20,0x20,0x20,0x20,0x73,0x74,0x64,0x3a,
    0x3a,0x63,0x6f,0x75,0x74,0x2e,0x66,0x6c,0x75,0x73,0x68,0x28,0x29,0x3b,0x0a,0x0a,
    0x20,0x20,0x20,0x20,0x7b,0x0a,0x09,0x45,0x6e,0x63,0x74,0x61,0x69,0x6e,0x3a,0x3a,
    0x43,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,
    0x6e,0x65,0x72,0x3b,0x0a,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,
    0x2e,0x53,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,0x70,0x65,0x72,
    0x74,0x79,0x28,0x22,0x70,0x72,0x6f,0x70,0x31,0x22,0x2c,0x20,0x22,0x74,0x65,0x73,
    0x74,0x20,0x61,0x62,0x63,0x22,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,
    0x6e,0x65,0x72,0x2e,0x53,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,
    0x70,0x65,0x72,0x74,0x79,0x28,0x22,0x70,0x72,0x6f,0x70,0x32,0x22,0x2c,0x20,0x73,
    0x74,0x64,0x3a,0x3a,0x73,0x74,0x72,0x69,0x6e,0x67,0x28,0x32,0x35,0x35,0x2c,0x20,
    0x27,0x61,0x27,0x29,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,
    0x72,0x2e,0x53,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,0x70,0x65,
    0x72,0x74,0x79,0x28,0x22,0x70,0x72,0x6f,0x70,0x33,0x22,0x2c,0x20,0x73,0x74,0x64,
    0x3a,0x3a,0x73,0x74,0x72,0x69,0x6e,0x67,0x28,0x32,0x35,0x36,0x2c,0x20,0x27,0x62,
    0x27,0x29,0x29,0x3b,0x0a,0x0a,0x09,0x75,0x6e,0x73,0x69,0x67,0x6e,0x65,0x64,0x20,
    0x69,0x6e,0x74,0x20,0x73,0x66,0x31,0x20,0x3d,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,
    0x6e,0x65,0x72,0x2e,0x41,0x70,0x70,0x65,0x6e,0x64,0x53,0x75,0x62,0x46,0x69,0x6c,
    0x65,0x28,0x29,0x3b,0x0a,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,
    0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x45,0x6e,0x63,0x72,0x79,
    0x70,0x74,0x69,0x6f,0x6e,0x28,0x73,0x66,0x31,0x2c,0x20,0x45,0x6e,0x63,0x74,0x61,
    0x69,0x6e,0x3a,0x3a,0x45,0x4e,0x43,0x52,0x59,0x50,0x54,0x49,0x4f,0x4e,0x5f,0x53,
    0x45,0x52,0x50,0x45,0x4e,0x54,0x32,0x35,0x36,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,
    0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,
    0x65,0x43,0x6f,0x6d,0x70,0x72,0x65,0x73,0x73,0x69,0x6f,0x6e,0x28,0x73,0x66,0x31,
    0x2c,0x20,0x45,0x6e,0x63,0x74,0x61,0x69,0x6e,0x3a,0x3a,0x43,0x4f,0x4d,0x50,0x52,
    0x45,0x53,0x53,0x49,0x4f,0x4e,0x5f,0x4e,0x4f,0x4e,0x45,0x29,0x3b,0x0a,0x0a,0x09,
    0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,
    0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x28,0x73,0x66,0x31,
    0x2c,0x20,0x22,0x4e,0x61,0x6d,0x65,0x22,0x2c,0x20,0x22,0x74,0x65,0x73,0x74,0x31,
    0x2e,0x74,0x78,0x74,0x22,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,
    0x65,0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,
    0x70,0x65,0x72,0x74,0x79,0x28,0x73,0x66,0x31,0x2c,0x20,0x22,0x4d,0x49,0x4d,0x45,
    0x2d,0x54,0x79,0x70,0x65,0x22,0x2c,0x20,0x22,0x74,0x65,0x78,0x74,0x2f,0x70,0x6c,
    0x61,0x69,0x6e,0x22,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,
    0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x44,0x61,0x74,0x61,
    0x28,0x73,0x66,0x31,0x2c,0x20,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x2c,0x20,
    0x73,0x69,0x7a,0x65,0x6f,0x66,0x28,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x29,
    0x29,0x3b,0x0a,0x0a,0x09,0x75,0x6e,0x73,0x69,0x67,0x6e,0x65,0x64,0x20,0x69,0x6e,
    0x74,0x20,0x73,0x66,0x32,0x20,0x3d,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,
    0x72,0x2e,0x41,0x70,0x70,0x65,0x6e,0x64,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x28,
    0x29,0x3b,0x0a,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x53,
    0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x45,0x6e,0x63,0x72,0x79,0x70,0x74,
    0x69,0x6f,0x6e,0x28,0x73,0x66,0x32,0x2c,0x20,0x45,0x6e,0x63,0x74,0x61,0x69,0x6e,
    0x3a,0x3a,0x45,0x4e,0x43,0x52,0x59,0x50,0x54,0x49,0x4f,0x4e,0x5f,0x53,0x45,0x52,
    0x50,0x45,0x4e,0x54,0x32,0x35,0x36,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,
    0x69,0x6e,0x65,0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x43,
    0x6f,0x6d,0x70,0x72,0x65,0x73,0x73,0x69,0x6f,0x6e,0x28,0x73,0x66,0x32,0x2c,0x20,
    0x45,0x6e,0x63,0x74,0x61,0x69,0x6e,0x3a,0x3a,0x43,0x4f,0x4d,0x50,0x52,0x45,0x53,
    0x53,0x49,0x4f,0x4e,0x5f,0x5a,0x4c,0x49,0x42,0x29,0x3b,0x0a,0x0a,0x09,0x63,0x6f,
    0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,
    0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x28,0x73,0x66,0x32,0x2c,0x20,
    0x22,0x4e,0x61,0x6d,0x65,0x22,0x2c,0x20,0x22,0x74,0x65,0x73,0x74,0x32,0x2e,0x74,
    0x78,0x74,0x22,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,
    0x2e,0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,
    0x72,0x74,0x79,0x28,0x73,0x66,0x32,0x2c,0x20,0x22,0x4d,0x49,0x4d,0x45,0x2d,0x54,
    0x79,0x70,0x65,0x22,0x2c,0x20,0x22,0x74,0x65,0x78,0x74,0x2f,0x70,0x6c,0x61,0x69,
    0x6e,0x22,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,
    0x53,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x44,0x61,0x74,0x61,0x28,0x73,
    0x66,0x32,0x2c,0x20,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x2c,0x20,0x73,0x69,
    0x7a,0x65,0x6f,0x66,0x28,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x29,0x29,0x3b,
    0x0a,0x0a,0x09,0x77,0x78,0x46,0x69,0x6c,0x65,0x4f,0x75,0x74,0x70,0x75,0x74,0x53,
    0x74,0x72,0x65,0x61,0x6d,0x20,0x6f,0x75,0x74,0x73,0x74,0x72,0x65,0x61,0x6d,0x28,
    0x5f,0x54,0x28,0x22,0x6f,0x75,0x74,0x2e,0x65,0x63,0x74,0x22,0x29,0x29,0x3b,0x0a,
    0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x53,0x61,0x76,0x65,0x28,
    0x6f,0x75,0x74,0x73,0x74,0x72,0x65,0x61,0x6d,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,
    0x7d,0x0a,0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,0x09,0x45,0x6e,0x63,0x74,0x61,0x69,
    0x6e,0x3a,0x3a,0x43,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x20,0x63,0x6f,0x6e,
    0x74,0x61,0x69,0x6e,0x65,0x72,0x3b,0x0a,0x0a,0x09,0x77,0x78,0x46,0x69,0x6c,0x65,
    0x49,0x6e,0x70,0x75,0x74,0x53,0x74,0x72,0x65,0x61,0x6d,0x20,0x69,0x6e,0x73,0x74,
    0x72,0x65,0x61,0x6d,0x28,0x5f,0x54,0x28,0x22,0x6f,0x75,0x74,0x2e,0x65,0x63,0x74,
    0x22,0x29,0x29,0x3b,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,
    0x4c,0x6f,0x61,0x64,0x28,0x69,0x6e,0x73,0x74,0x72,0x65,0x61,0x6d,0x2c,0x20,0x22,
    0x61,0x62,0x63,0x22,0x29,0x3b,0x0a,0x09,0x0a,0x09,0x73,0x74,0x64,0x3a,0x3a,0x73,
    0x74,0x72,0x69,0x6e,0x67,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x3b,0x0a,
    0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,
    0x65,0x72,0x2e,0x47,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,0x70,
    0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,0x28,0x30,0x2c,0x20,0x6b,0x65,0x79,
    0x2c,0x20,0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,
    0x74,0x28,0x20,0x6b,0x65,0x79,0x20,0x3d,0x3d,0x20,0x22,0x70,0x72,0x6f,0x70,0x31,
    0x22,0x20,0x26,0x26,0x20,0x76,0x61,0x6c,0x20,0x3d,0x3d,0x20,0x22,0x74,0x65,0x73,
    0x74,0x20,0x61,0x62,0x63,0x22,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,
    0x74,0x28,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,
    0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,
    0x64,0x65,0x78,0x28,0x31,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x29,
    0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6b,0x65,0x79,
    0x20,0x3d,0x3d,0x20,0x22,0x70,0x72,0x6f,0x70,0x32,0x22,0x20,0x26,0x26,0x20,0x76,
    0x61,0x6c,0x20,0x3d,0x3d,0x20,0x73,0x74,0x64,0x3a,0x3a,0x73,0x74,0x72,0x69,0x6e,
    0x67,0x28,0x32,0x35,0x35,0x2c,0x20,0x27,0x61,0x27,0x29,0x20,0x29,0x3b,0x0a,0x09,
    0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,
    0x72,0x2e,0x47,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,0x6c,0x50,0x72,0x6f,0x70,0x65,
    0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,0x28,0x32,0x2c,0x20,0x6b,0x65,0x79,0x2c,
    0x20,0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,
    0x28,0x20,0x6b,0x65,0x79,0x20,0x3d,0x3d,0x20,0x22,0x70,0x72,0x6f,0x70,0x33,0x22,
    0x20,0x26,0x26,0x20,0x76,0x61,0x6c,0x20,0x3d,0x3d,0x20,0x73,0x74,0x64,0x3a,0x3a,
    0x73,0x74,0x72,0x69,0x6e,0x67,0x28,0x32,0x35,0x36,0x2c,0x20,0x27,0x62,0x27,0x29,
    0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x21,0x63,0x6f,
    0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x47,0x6c,0x6f,0x62,0x61,
    0x6c,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,0x28,0x33,
    0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,0x0a,
    0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,
    0x72,0x2e,0x43,0x6f,0x75,0x6e,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x28,0x29,
    0x20,0x3d,0x3d,0x20,0x32,0x29,0x3b,0x0a,0x0a,0x09,0x2f,0x2f,0x20,0x73,0x75,0x62,
    0x66,0x69,0x6c,0x65,0x20,0x30,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,
    0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x53,0x75,0x62,
    0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,
    0x78,0x28,0x30,0x2c,0x20,0x30,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,
    0x29,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6b,0x65,
    0x79,0x20,0x3d,0x3d,0x20,0x22,0x4d,0x49,0x4d,0x45,0x2d,0x54,0x79,0x70,0x65,0x22,
    0x20,0x26,0x26,0x20,0x76,0x61,0x6c,0x20,0x3d,0x3d,0x20,0x22,0x74,0x65,0x78,0x74,
    0x2f,0x70,0x6c,0x61,0x69,0x6e,0x22,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,
    0x72,0x74,0x28,0x20,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,
    0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,
    0x49,0x6e,0x64,0x65,0x78,0x28,0x30,0x2c,0x20,0x31,0x2c,0x20,0x6b,0x65,0x79,0x2c,
    0x20,0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,
    0x28,0x20,0x6b,0x65,0x79,0x20,0x3d,0x3d,0x20,0x22,0x4e,0x61,0x6d,0x65,0x22,0x20,
    0x26,0x26,0x20,0x76,0x61,0x6c,0x20,0x3d,0x3d,0x20,0x22,0x74,0x65,0x73,0x74,0x31,
    0x2e,0x74,0x78,0x74,0x22,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,
    0x28,0x20,0x21,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,
    0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,
    0x6e,0x64,0x65,0x78,0x28,0x30,0x2c,0x20,0x32,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,
    0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,0x0a,0x09,0x77,0x78,0x4d,0x65,0x6d,0x6f,
    0x72,0x79,0x42,0x75,0x66,0x66,0x65,0x72,0x20,0x6d,0x62,0x3b,0x0a,0x09,0x63,0x6f,
    0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x53,0x75,0x62,0x46,0x69,
    0x6c,0x65,0x44,0x61,0x74,0x61,0x28,0x30,0x2c,0x20,0x6d,0x62,0x29,0x3b,0x0a,0x09,
    0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6d,0x62,0x2e,0x47,0x65,0x74,
    0x44,0x61,0x74,0x61,0x4c,0x65,0x6e,0x28,0x29,0x20,0x3d,0x3d,0x20,0x73,0x69,0x7a,
    0x65,0x6f,0x66,0x28,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x29,0x20,0x29,0x3b,
    0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6d,0x65,0x6d,0x63,0x6d,0x70,
    0x28,0x6d,0x62,0x2e,0x47,0x65,0x74,0x44,0x61,0x74,0x61,0x28,0x29,0x2c,0x20,0x74,
    0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x2c,0x20,0x73,0x69,0x7a,0x65,0x6f,0x66,0x28,
    0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x29,0x29,0x20,0x3d,0x3d,0x20,0x30,0x20,
    0x29,0x3b,0x0a,0x0a,0x09,0x2f,0x2f,0x20,0x73,0x75,0x62,0x66,0x69,0x6c,0x65,0x20,
    0x31,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x63,0x6f,0x6e,0x74,0x61,
    0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x50,
    0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,0x28,0x31,0x2c,0x20,
    0x30,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x29,0x20,0x29,0x3b,0x0a,
    0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6b,0x65,0x79,0x20,0x3d,0x3d,0x20,
    0x22,0x4d,0x49,0x4d,0x45,0x2d,0x54,0x79,0x70,0x65,0x22,0x20,0x26,0x26,0x20,0x76,
    0x61,0x6c,0x20,0x3d,0x3d,0x20,0x22,0x74,0x65,0x78,0x74,0x2f,0x70,0x6c,0x61,0x69,
    0x6e,0x22,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x63,
    0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x53,0x75,0x62,0x46,
    0x69,0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,
    0x28,0x31,0x2c,0x20,0x31,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x29,
    0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x6b,0x65,0x79,
    0x20,0x3d,0x3d,0x20,0x22,0x4e,0x61,0x6d,0x65,0x22,0x20,0x26,0x26,0x20,0x76,0x61,
    0x6c,0x20,0x3d,0x3d,0x20,0x22,0x74,0x65,0x73,0x74,0x32,0x2e,0x74,0x78,0x74,0x22,
    0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,0x20,0x21,0x63,0x6f,
    0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,0x65,0x74,0x53,0x75,0x62,0x46,0x69,
    0x6c,0x65,0x50,0x72,0x6f,0x70,0x65,0x72,0x74,0x79,0x49,0x6e,0x64,0x65,0x78,0x28,
    0x31,0x2c,0x20,0x32,0x2c,0x20,0x6b,0x65,0x79,0x2c,0x20,0x76,0x61,0x6c,0x29,0x20,
    0x29,0x3b,0x0a,0x0a,0x09,0x63,0x6f,0x6e,0x74,0x61,0x69,0x6e,0x65,0x72,0x2e,0x47,
    0x65,0x74,0x53,0x75,0x62,0x46,0x69,0x6c,0x65,0x44,0x61,0x74,0x61,0x28,0x31,0x2c,
    0x20,0x6d,0x62,0x29,0x3b,0x0a,0x09,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,
    0x20,0x6d,0x62,0x2e,0x47,0x65,0x74,0x44,0x61,0x74,0x61,0x4c,0x65,0x6e,0x28,0x29,
    0x20,0x3d,0x3d,0x20,0x73,0x69,0x7a,0x65,0x6f,0x66,0x28,0x74,0x65,0x73,0x74,0x74,
    0x65,0x78,0x74,0x29,0x20,0x29,0x3b,0x0a,0x09,0x61,0x73,0x73,0x65,0x72,0x74,0x28,
    0x20,0x6d,0x65,0x6d,0x63,0x6d,0x70,0x28,0x6d,0x62,0x2e,0x47,0x65,0x74,0x44,0x61,
    0x74,0x61,0x28,0x29,0x2c,0x20,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x2c,0x20,
    0x73,0x69,0x7a,0x65,0x6f,0x66,0x28,0x74,0x65,0x73,0x74,0x74,0x65,0x78,0x74,0x29,
    0x29,0x20,0x3d,0x3d,0x20,0x30,0x20,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x7d,0x0a,
    0x0a,0x20,0x20,0x20,0x20,0x73,0x74,0x64,0x3a,0x3a,0x63,0x6f,0x75,0x74,0x20,0x3c,
    0x3c,0x20,0x22,0x4f,0x4b,0x5c,0x6e,0x22,0x3b,0x0a,0x0a,0x20,0x20,0x20,0x20,0x72,
    0x65,0x74,0x75,0x72,0x6e,0x20,0x30,0x3b,0x0a,0x7d,0x0a
};

struct DataOutputStream : public Enctain::DataOutput
{
    std::ostream&	os;

    DataOutputStream(std::ostream& s)
	: os(s)
    {
    }

    virtual bool Output(const void* data, size_t datalen)
    {
	os.write((const char*)data, datalen).good();
	os.flush();
	return true;
    }
};

struct DataInputStream : public Enctain::DataInput
{
    std::istream&	is;

    DataInputStream(std::istream& s)
	: is(s)
    {
    }

    virtual unsigned int Input(void* data, size_t maxlen)
    {
	return is.read((char*)data, maxlen).gcount();
    }
};

void test_enctain(const std::string& filedata, std::string filename)
{
    std::ostringstream memfile;
    filename.size();

    {
	Enctain::Container container;

	container.SetGlobalUnencryptedProperty("prop1", "test abc");

	container.SetGlobalEncryptedProperty("secret1", "blah");

	container.SetGlobalEncryptedProperty("prop2", std::string(255, 'a'));
	container.SetGlobalEncryptedProperty("prop3", std::string(256, 'b'));

	unsigned int sf1 = container.AppendSubFile();

	container.SetSubFileEncryption(sf1, Enctain::ENCRYPTION_NONE);
	container.SetSubFileCompression(sf1, Enctain::COMPRESSION_NONE);

	container.SetSubFileProperty(sf1, "Name", "test1.txt");
	container.SetSubFileProperty(sf1, "MIME-Type", "text/plain");
	container.SetSubFileData(sf1, filedata.data(), filedata.size());

	unsigned int sf2 = container.AppendSubFile();

	container.SetSubFileEncryption(sf2, Enctain::ENCRYPTION_NONE);
	container.SetSubFileCompression(sf2, Enctain::COMPRESSION_ZLIB);

	container.SetSubFileProperty(sf2, "Name", "test2.txt");
	container.SetSubFileProperty(sf2, "MIME-Type", "text/plain");
	container.SetSubFileData(sf2, filedata.data(), filedata.size());

	container.AddKeySlot("oYLiP4Td");

	unsigned int sf3 = container.AppendSubFile();

	container.SetSubFileEncryption(sf3, Enctain::ENCRYPTION_NONE);
	container.SetSubFileCompression(sf3, Enctain::COMPRESSION_BZIP2);

	container.SetSubFileProperty(sf3, "Name", "test3.txt");
	container.SetSubFileProperty(sf3, "MIME-Type", "text/plain");
	container.SetSubFileData(sf3, filedata.data(), filedata.size());

	unsigned int sf4 = container.AppendSubFile();

	container.SetSubFileEncryption(sf4, Enctain::ENCRYPTION_SERPENT256);
	container.SetSubFileCompression(sf4, Enctain::COMPRESSION_NONE);

	container.SetSubFileProperty(sf4, "Name", "test4.txt");
	container.SetSubFileProperty(sf4, "MIME-Type", "text/plain");
	container.SetSubFileData(sf4, filedata.data(), filedata.size());

	unsigned int sf5 = container.AppendSubFile();

	container.SetSubFileEncryption(sf5, Enctain::ENCRYPTION_SERPENT256);
	container.SetSubFileCompression(sf5, Enctain::COMPRESSION_ZLIB);

	container.SetSubFileProperty(sf5, "Name", "test5.txt");
	container.SetSubFileProperty(sf5, "MIME-Type", "text/plain");
	container.SetSubFileData(sf5, filedata.data(), filedata.size());

	container.AddKeySlot("ELO0Eia9");

	unsigned int sf6 = container.AppendSubFile();

	container.SetSubFileEncryption(sf6, Enctain::ENCRYPTION_SERPENT256);
	container.SetSubFileCompression(sf6, Enctain::COMPRESSION_BZIP2);

	container.SetSubFileProperty(sf6, "Name", "test6.txt");
	container.SetSubFileProperty(sf6, "MIME-Type", "text/plain");
	container.SetSubFileData(sf6, filedata.data(), filedata.size());

#if WRITEFILE == 0
	DataOutputStream dataout(memfile);
#else
	std::ofstream outstream(filename.c_str());
	DataOutputStream dataout(outstream);
#endif

	container.Save(dataout);
    }

    {
	Enctain::Container container;

#if WRITEFILE == 0
	std::istringstream instream(memfile.str());
#else
	std::ifstream instream(filename.c_str());
#endif

	DataInputStream datain(instream);
	container.Load(datain, "ELO0Eia9");

	std::string key, val;
	assert( container.GetGlobalUnencryptedPropertyIndex(0, key, val) );
	assert( key == "prop1" && val == "test abc" );
	assert( !container.GetGlobalUnencryptedPropertyIndex(1, key, val) );

	assert( container.GetGlobalEncryptedPropertyIndex(0, key, val) );
	assert( key == "prop2" && val == std::string(255, 'a') );
	assert( container.GetGlobalEncryptedPropertyIndex(1, key, val) );
	assert( key == "prop3" && val == std::string(256, 'b') );
	assert( container.GetGlobalEncryptedPropertyIndex(2, key, val) );
	assert( key == "secret1" && val == "blah" );
	assert( !container.GetGlobalEncryptedPropertyIndex(3, key, val) );

	assert(container.CountSubFile() == 6);

	// subfile 0
	assert( container.GetSubFilePropertyIndex(0, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(0, 1, key, val) );
	assert( key == "Name" && val == "test1.txt" );
	assert( !container.GetSubFilePropertyIndex(0, 2, key, val) );

	std::string mb;
	container.GetSubFileData(0, mb);
	
	assert( mb == filedata );

	// subfile 1
	assert( container.GetSubFilePropertyIndex(1, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(1, 1, key, val) );
	assert( key == "Name" && val == "test2.txt" );
	assert( !container.GetSubFilePropertyIndex(1, 2, key, val) );

	container.GetSubFileData(1, mb);
	assert( mb == filedata );

	// subfile 2
	assert( container.GetSubFilePropertyIndex(2, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(2, 1, key, val) );
	assert( key == "Name" && val == "test3.txt" );
	assert( !container.GetSubFilePropertyIndex(2, 2, key, val) );

	container.GetSubFileData(2, mb);
	assert( mb == filedata );

	// subfile 3
	assert( container.GetSubFilePropertyIndex(3, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(3, 1, key, val) );
	assert( key == "Name" && val == "test4.txt" );
	assert( !container.GetSubFilePropertyIndex(3, 2, key, val) );

	container.GetSubFileData(3, mb);
	assert( mb == filedata );

	// subfile 4
	assert( container.GetSubFilePropertyIndex(4, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(4, 1, key, val) );
	assert( key == "Name" && val == "test5.txt" );
	assert( !container.GetSubFilePropertyIndex(4, 2, key, val) );

	container.GetSubFileData(4, mb);
	assert( mb == filedata );

	// subfile 5
	assert( container.GetSubFilePropertyIndex(5, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(5, 1, key, val) );
	assert( key == "Name" && val == "test6.txt" );
	assert( !container.GetSubFilePropertyIndex(5, 2, key, val) );

	container.GetSubFileData(5, mb);
	assert( mb == filedata );

	// subfile 5 (again)
	assert( container.GetSubFilePropertyIndex(5, 0, key, val) );
	assert( key == "MIME-Type" && val == "text/plain" );
	assert( container.GetSubFilePropertyIndex(5, 1, key, val) );
	assert( key == "Name" && val == "test6.txt" );
	assert( !container.GetSubFilePropertyIndex(5, 2, key, val) );

	container.GetSubFileData(5, mb);
	assert( mb == filedata );
    }
}

int main()
{
    Enctain::LibraryInitializer init;

    srand(time(NULL));

    std::cout << "Testing Encrypted Container implementation...";
    std::cout.flush();

    Enctain::Container::SetSignature("CryptoTE");

    // First test is with some real text (source code)
    test_enctain( std::string(testtext, sizeof(testtext)), "test1.ect" );

    // Second is a 1MB sized generated text
    std::string gen1000;
    for(unsigned int i = 0; i < 1024*1024; ++i)
    {
	gen1000 += (unsigned char)(i*i);
    }

    test_enctain( gen1000, "test2.ect" );

    // Second is a 1MB sized random text
    std::string rand1000;
    for(unsigned int i = 0; i < 1024*1024; ++i)
    {
	rand1000 += (unsigned char)rand();
    }

    test_enctain( rand1000, "test3.ect" );

    std::cout << "OK\n";

    return 0;
}
