/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.polysfactory.facerecognition.jni;

import com.opencv.jni.*; //import the android-opencv jni wrappers

class NativeFaceRecognizerJNI {

	static {
		try {
			//load the cvcamera library, make sure that libcvcamera.so is in your <project>/libs/armeabi directory
			//so that android sdk automatically installs it along with the app.
			
			//the android-opencv lib must be loaded first inorder for the cvcamera
			//lib to be found
			//check the apk generated, by opening it in an archive manager, to verify that
			//both these libraries are present
			System.loadLibrary("android-opencv");
			System.loadLibrary("FaceRecognizer");
		} catch (UnsatisfiedLinkError e) {
			//badness
			throw e;
		}
	}


  public final static native long new_FaceRecognizer();
  public final static native int FaceRecognizer_recognize(long jarg1, FaceRecognizer jarg1_, int jarg2, long jarg3, image_pool jarg3_);
  public final static native void delete_FaceRecognizer(long jarg1);
}
