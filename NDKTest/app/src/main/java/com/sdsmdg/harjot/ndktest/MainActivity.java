package com.sdsmdg.harjot.ndktest;

import android.graphics.Bitmap;
import android.graphics.Path;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;

public class MainActivity extends AppCompatActivity {

    ImageView imgSrc, imgDest;
    boolean isLoaded = false;

    CustomView customView;

    private BaseLoaderCallback _baseLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS: {
                    Log.i("OPEN_CV", "OpenCV loaded successfully");
                    System.loadLibrary("native-lib");
                    isLoaded = true;
                }
                break;
                default: {
                    super.onManagerConnected(status);
                }
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imgSrc = (ImageView) findViewById(R.id.img_src);
        imgDest = (ImageView) findViewById(R.id.img_dest);

        customView = (CustomView) findViewById(R.id.custom_view);
        customView.setLayerType(View.LAYER_TYPE_SOFTWARE, null);

        imgSrc.post(new Runnable() {
            @Override
            public void run() {
                if (isLoaded)
                    convertToGrayscale();
            }
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d("OPEN_CV", "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_1_0, this, _baseLoaderCallback);
        } else {
            Log.d("OPEN_CV", "OpenCV library found inside package. Using it!");
            _baseLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }


    void convertToGrayscale() {

        Log.d("TIMING", "1");

        imgSrc.buildDrawingCache();
        Bitmap bitmap = imgSrc.getDrawingCache();

        Mat srcMat = new Mat();
        Utils.bitmapToMat(bitmap, srcMat);

        Mat destMat = new Mat();

        Point[] points = convert(srcMat.getNativeObjAddr(), destMat.getNativeObjAddr());

        Path path = new Path();
        path.moveTo(points[0].getX(), points[0].getY());
        for (int i = 1; i < points.length; i++) {
            if (points[i].getX() == -1 && points[i].getY() == -1) {
                if (i + 1 < points.length) {
                    path.moveTo(points[i + 1].getX(), points[i + 1].getY());
                }
                i++;
            } else {
                path.lineTo(points[i].getX(), points[i].getY());
            }
        }

        customView.setPath(path);

//        Bitmap bitmapDest = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
//        Utils.matToBitmap(destMat, bitmapDest);
//
//        imgDest.setImageBitmap(bitmapDest);


        Log.d("TIMING", "2");

    }

    public native Point[] convert(long srcAddr, long destAddr);

}
