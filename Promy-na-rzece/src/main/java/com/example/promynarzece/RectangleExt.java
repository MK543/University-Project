package com.example.promynarzece;

import javafx.scene.shape.Rectangle;
import javafx.scene.paint.Color;

public class RectangleExt {

    Rectangle rectangle;
    boolean isOccupied;
    RectangleExt(int width, int height, Color color){
        this.isOccupied = false;
        this.rectangle = new Rectangle(width, height, color);
    }
}
