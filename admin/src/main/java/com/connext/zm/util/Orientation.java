package com.connext.zm.util;

/** @Author: Marcus @Date: 2019/4/29 10:54 @Version 1.0 */
public enum Orientation {
  SN,
  EW;

  public static Orientation getOppositeOrientation(String var1) {
    Orientation source = Orientation.valueOf(var1);
    for (Orientation temp : Orientation.values()) {
      if (!temp.equals(source)) {
        return temp;
      }
    }
    return null;
  }
}
