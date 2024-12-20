// Copyright (c) rice-timer authors
#pragma once

enum class Lsm6Reg : uint8_t {
  PIN_CTRL = 0x02,
  FIFO_CTRL1 = 0x07,
  FIFO_CTRL2 = 0x08,
  FIFO_CTRL3 = 0x09,
  FIFO_CTRL4 = 0x0A,
  COUNTER_BDR_REG1 = 0x0B,
  COUNTER_BDR_REG2 = 0x0C,
  INT1_CTRL = 0x0D,
  INT2_CTRL = 0x0E,
  WHO_AM_I = 0x0F,
  CTRL1_XL = 0x10,
  CTRL2_G = 0x11,
  CTRL3_C = 0x12,
  CTRL4_C = 0x13,
  CTRL5_C = 0x14,
  CTRL6_C = 0x15,
  CTRL7_G = 0x16,
  CTRL8_XL = 0x17,
  CTRL9_XL = 0x18,
  CTRL10_C = 0x19,
  ALL_INT_SRC = 0x1A,
  WAKE_UP_SRC = 0x1B,
  D6D_SRC = 0x1D,
  STATUS_REG = 0x1E,
  OUT_TEMP_L = 0x20,
  OUT_TEMP_H = 0x21,
  OUTX_L_G = 0x22,
  OUTX_H_G = 0x23,
  OUTY_L_G = 0x24,
  OUTY_H_G = 0x25,
  OUTZ_L_G = 0x26,
  OUTZ_H_G = 0x27,
  OUTX_L_A = 0x28,
  OUTX_H_A = 0x29,
  OUTY_L_A = 0x2A,
  OUTY_H_A = 0x2B,
  OUTZ_L_A = 0x2C,
  OUTZ_H_A = 0x2D,
  FIFO_STATUS1 = 0x3A,
  FIFO_STATUS2 = 0x3B,
  TIMESTAMP0_REG = 0x40,
  TIMESTAMP1_REG = 0x41,
  TIMESTAMP2_REG = 0x42,
  TIMESTAMP3_REG = 0x43,
  INT_CFG0 = 0x56,
  INT_CFG1 = 0x58,
  THS_6D = 0x59,
  WAKE_UP_THS = 0x5B,
  WAKE_UP_DUR = 0x5C,
  FREE_FALL = 0x5D,
  MD1_CFG = 0x5E,
  MD2_CFG = 0x5F,
  INTERNAL_FREQ_FINE = 0x63,
  X_OFS_USR = 0x73,
  Y_OFS_USR = 0x74,
  Z_OFS_USR = 0x75,
  FIFO_DATA_OUT_TAG = 0x78,
  FIFO_DATA_OUT_X_L = 0x79,
  FIFO_DATA_OUT_X_H = 0x7A,
  FIFO_DATA_OUT_Y_L = 0x7B,
  FIFO_DATA_OUT_Y_H = 0x7C,
  FIFO_DATA_OUT_Z_L = 0x7D,
  FIFO_DATA_OUT_Z_H = 0x7E,
};