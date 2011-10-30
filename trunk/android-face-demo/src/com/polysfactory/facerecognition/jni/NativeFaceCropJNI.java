/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.polysfactory.facerecognition.jni;

import com.opencv.jni.*; //import the android-opencv jni wrappers

public class NativeFaceCropJNI {

	static {
		try {
			//load the cvcamera library, make sure that libcvcamera.so is in your <project>/libs/armeabi directory
			//so that android sdk automatically installs it along with the app.
			
			//the android-opencv lib must be loaded first inorder for the cvcamera
			//lib to be found
			//check the apk generated, by opening it in an archive manager, to verify that
			//both these libraries are present
      System.loadLibrary("android-opencv");
			System.loadLibrary("FaceCrop");
		} catch (UnsatisfiedLinkError e) {
			//badness
			throw e;
		}
	}


  public final static native long new_FaceCrop();
  public final static native void delete_FaceCrop(long jarg1);
  public final static native boolean FaceCrop_crop(long jarg1, FaceCrop jarg1_, String jarg2);
}
