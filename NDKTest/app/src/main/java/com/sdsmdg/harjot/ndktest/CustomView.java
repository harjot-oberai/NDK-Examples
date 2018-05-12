package com.sdsmdg.harjot.ndktest;

import android.content.Context;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.view.View;

/**
 * Created by Harjot on 18-Jun-17.
 */

public class CustomView extends View {

    Path path;
    Paint paint;

    float offsetX, offsetY;

    public CustomView(Context context) {
        super(context);
        init();
    }

    public CustomView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public CustomView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    void init() {

        offsetX = 0.0f;
        offsetY = 0.0f;

        paint = new Paint();
        paint.setAntiAlias(true);
        paint.setColor(Color.parseColor("#121212"));
//        paint.setMaskFilter(new BlurMaskFilter(8, BlurMaskFilter.Blur.NORMAL));
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeWidth(3.0f);
    }

    public Path getPath() {
        return path;
    }

    public void setPath(Path path) {
        this.path = path;
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if (path != null) {
            path.offset(offsetX, offsetY);
            canvas.drawPath(path, paint);
        }
    }
}
