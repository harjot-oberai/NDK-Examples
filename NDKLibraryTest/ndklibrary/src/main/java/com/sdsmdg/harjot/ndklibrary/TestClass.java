package com.sdsmdg.harjot.ndklibrary;

/**
 * Created by Harjot on 21-Jan-18.
 */

public class TestClass {

    static {
        System.loadLibrary("test");
    }

    public native String stringFromJNI();

}
