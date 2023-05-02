package com.example.promynarzece;
import javafx.animation.Animation;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Configuration {
    int screenWidth;
    int screenHeight;
    int shipsNumber;
    int carsNumber;
    int harbourCapacity;
    int shipCapacity;

    int squareSize;

    int circleRadius;

    int squareSpace;

    public XYCoord[] carsSquareCoords;

    public XYCoord[] carsCircleCoords;

    public XYCoord[] harbourSquareCoords;

    public XYCoord[] harbourCircleCoords;


    public XYCoord[][] shipSpotsSquareCoords;

    public XYCoord[][] shipSpotsCircleCoords;

    public XYCoord[] shipsSquareCoords;

    public XYCoord[] shipsCircleCoords;

    public int carsSquareYref = 565;
    public int harbourSquareYref = 405;
    public int shipSquareYref = 45;
    public int shipsSpotsYref = 115;
    public int bigSquareSize;
    public int bigSquareSpace;

    public double shipSpeed;
    public double carSpeed;

    public Configuration(int screenWidth, int screenHeight, int shipsNumber, int carsNumber, int harbourCapacity, int shipCapacity){
        this.screenWidth = screenWidth;
        this.screenHeight = screenHeight;
        this.shipsNumber = shipsNumber;
        this.carsNumber = carsNumber;
        this.harbourCapacity = harbourCapacity;
        this.shipCapacity = shipCapacity;


        //Cars
        squareSize = 50;
        circleRadius = 20;
        squareSpace = 10;
        int free_space = screenWidth;

        //Ships
        bigSquareSize = 60;
        bigSquareSpace = 100;

        // Initial deployment of cars' squares and circles
        //
        System.out.println(free_space);
        int xref = (free_space-10*(squareSize + squareSpace) + squareSpace) / 2;
        int overflow = 0;
        carsSquareCoords = new XYCoord[carsNumber];
        carsCircleCoords = new XYCoord[carsNumber];
        for (int i = 0; i < carsSquareCoords.length; i++) {

            carsSquareCoords[i] = new XYCoord();
            carsSquareCoords[i].x = xref + (i-overflow*10) * (squareSize + squareSpace);
            carsSquareCoords[i].y = carsSquareYref + overflow* (squareSize+squareSpace);

            carsCircleCoords[i] = new XYCoord();
            carsCircleCoords[i].x = carsSquareCoords[i].x + squareSize / 2;
            carsCircleCoords[i].y = carsSquareCoords[i].y + squareSize / 2;
            if(i%10 == 9){
                overflow++;
            }
        }

        // Initial deployment of harbour's squares and circles
        //
        free_space = screenWidth - harbourCapacity * squareSize;
        xref = free_space / 2;
        harbourSquareCoords = new XYCoord[harbourCapacity];
        harbourCircleCoords = new XYCoord[harbourCapacity];
        for (int i = 0; i < harbourSquareCoords.length; i++) {

            harbourSquareCoords[i] = new XYCoord();
            harbourSquareCoords[i].x = xref + i * squareSize;
            harbourSquareCoords[i].y = harbourSquareYref;

            harbourCircleCoords[i] = new XYCoord();
            harbourCircleCoords[i].x = harbourSquareCoords[i].x + squareSize / 2;
            harbourCircleCoords[i].y = harbourSquareCoords[i].y + squareSize / 2;
        }

        // Initial deployment of ships' squares and circles
        //
        free_space = screenWidth - shipsNumber * (bigSquareSize + bigSquareSpace) + bigSquareSpace;
        xref = free_space / 2;
        shipsSquareCoords = new XYCoord[shipsNumber];
        shipsCircleCoords = new XYCoord[shipsNumber];
        for(int i = 0; i< shipsSquareCoords.length; i++){

            shipsSquareCoords[i] = new XYCoord();
            shipsSquareCoords[i].x = xref + i * (bigSquareSize + bigSquareSpace);
            shipsSquareCoords[i].y = shipSquareYref;

            shipsCircleCoords[i] = new XYCoord();
            shipsCircleCoords[i].x = shipsSquareCoords[i].x + bigSquareSize / 2;
            shipsCircleCoords[i].y = shipsSquareCoords[i].y + bigSquareSize / 2;
        }
        int odd;
        int height;
        shipSpotsSquareCoords = new XYCoord[shipsNumber][shipCapacity];
        shipSpotsCircleCoords = new XYCoord[shipsNumber][shipCapacity];
        for(int i = 0; i<shipsNumber; i++){
            height = 0;
            odd = 0;
            for(int j = 0; j<shipCapacity; j++){

                shipSpotsSquareCoords[i][j] = new XYCoord();
                shipSpotsSquareCoords[i][j].x = shipsSquareCoords[i].x + odd*( squareSize+ squareSpace)-squareSize/2;
                shipSpotsSquareCoords[i][j].y = shipsSpotsYref + squareSize*height;

                shipSpotsCircleCoords[i][j] = new XYCoord();
                shipSpotsCircleCoords[i][j].x = shipSpotsSquareCoords[i][j].x + squareSize/2;
                shipSpotsCircleCoords[i][j].y = shipSpotsSquareCoords[i][j].y + squareSize/2;
                odd++;
                odd = odd % 2;
                height = height + j%2;
            }
        }
    }

    Rectangle[] carsSquares;
    Circle[] carsCircles;
    Rectangle[] harbourSquares;
    Rectangle[] shipsSquares;
    Rectangle[][] shipSpots;
    Label[] shipLabels;
    Label[] shipNamesLabels;

    List<Animation> shipsAnimations;
    List<Animation> carsAnimations;

    public void prepareAnimation() {
        carSpeed = 0.5;
        shipSpeed = 0.5;
        carsSquares = new Rectangle[carsNumber];
        carsCircles = new Circle[carsNumber];
        shipLabels = new Label[shipsNumber];
        shipNamesLabels = new Label[shipsNumber];
        shipsAnimations = new ArrayList<Animation>();
        carsAnimations = new ArrayList<Animation>();

        harbourSquares = new Rectangle[harbourCapacity];
        for (int i = 0; i < harbourSquares.length; i++) {
            harbourSquares[i] = new Rectangle(harbourSquareCoords[i].x, harbourSquareCoords[i].y, squareSize, squareSize);
            harbourSquares[i].setFill(Color.WHITE);
            harbourSquares[i].setStroke(Color.BLACK);
            harbourSquares[i].setStrokeWidth(2.0);
            Main.animationPane.getChildren().add(harbourSquares[i]);
        }

        shipsSquares = new Rectangle[shipsNumber];
        for (int i = 0; i < shipsSquares.length; i++) {
            shipsSquares[i] = new Rectangle(shipsSquareCoords[i].x, shipsSquareCoords[i].y, bigSquareSize, bigSquareSize);
            shipsSquares[i].setFill(Color.WHITE);
            shipsSquares[i].setStroke(Color.BLACK);
            shipsSquares[i].setStrokeWidth(2.0);

            shipLabels[i] = new Label("Status: Animation off");
            shipLabels[i].setLayoutX(shipsSquareCoords[i].x);
            shipLabels[i].setLayoutY(shipsSquareCoords[i].y-18);

            shipNamesLabels[i] = new Label("Ship-"+i);
            shipNamesLabels[i].setLayoutX(shipsSquareCoords[i].x);
            shipNamesLabels[i].setLayoutY(shipsSquareCoords[i].y-36);
            Main.animationPane.getChildren().addAll(shipsSquares[i], shipLabels[i], shipNamesLabels[i]);
        }

        shipSpots = new Rectangle[shipsNumber][shipCapacity];
        for(int i = 0; i<shipsNumber; i++){
            for(int j = 0; j<shipCapacity; j++){
                shipSpots[i][j] = new Rectangle(shipSpotsSquareCoords[i][j].x, shipSpotsSquareCoords[i][j].y, squareSize, squareSize);
                shipSpots[i][j].setFill(Color.WHITE);
                shipSpots[i][j].setStroke(Color.BLACK);
                shipSpots[i][j].setStrokeWidth(2.0);

                Main.animationPane.getChildren().add(shipSpots[i][j]);
            }
        }

        for (int i = 0; i < carsSquares.length; i++) {
            carsSquares[i] = new Rectangle(carsSquareCoords[i].x, carsSquareCoords[i].y, squareSize, squareSize);
            carsSquares[i].setFill(Color.WHITE);
            carsSquares[i].setStroke(Color.BLACK);
            carsSquares[i].setStrokeWidth(2.0);

            carsCircles[i] = new Circle(carsCircleCoords[i].x, carsCircleCoords[i].y, circleRadius);
            carsCircles[i].setFill(Color.color(Math.random() % 255, Math.random() % 255, Math.random() % 255));
            carsCircles[i].setStroke(Color.BLACK);
            carsCircles[i].setStrokeWidth(2.0);
            carsCircles[i].setScaleX(0);
            carsCircles[i].setScaleY(0);
            carsCircles[i].toFront();

            Main.animationPane.getChildren().add(carsSquares[i]);
            Main.animationPane.getChildren().add(carsCircles[i]);

        }


    }
    Ship[] ships;
    Car[] cars;

    Harbour harbour;


    public void startThreads(){
        harbour = new Harbour(harbourCapacity, harbourCircleCoords, this);
        ships = new Ship[shipsNumber];
        cars = new Car[carsNumber];
        int repCar = 1000;
        int repShip = 2000;

        //Creating objects
        for(int i = 0; i<cars.length; i++){
            cars[i] = new Car(harbour,"Car-"+i, repCar, i, carsCircles[i], carsCircleCoords[i]);
        }
        for(int i = 0; i<ships.length; i++){
            ships[i] = new Ship("Ship-"+i, shipCapacity, 0, harbour, i, repShip, shipSpotsCircleCoords[i], this);
        }

        //Starting objects
        for(int i = 0; i<cars.length; i++){
            cars[i].start();
        }
        for(int i = 0; i<ships.length; i++){
           ships[i].start();
        }
    }

    public void interruptThreads() throws InterruptedException {
        for (int i = 0; i < cars.length; i++) {
           cars[i].interrupt();
        }
        for (int i = 0; i < ships.length; i++) {
            ships[i].interrupt();
        }
        /*for (int i = 0; i < cars.length; i++) {
            cars[i].join();
        }*/
        /*for (int i = 0; i < ships.length; i++) {
            ships[i].join();
        }*/
        Arrays.fill(harbour.isOccupied, false);
        for(int i = 0; i < ships.length; i++){
            for(int j = 0; j < shipCapacity; j++){
                ships[i].isOccupied[j] = false;
            }
        }
    }

    public void shipsAnimationSpeedChange(double sliderValue){
        // -100 <= sliderValue <= 100
        //
        if(sliderValue >= 0){
            shipSpeed = 0.5 - sliderValue * 0.004;
        }
        else{
            shipSpeed = 0.5 - sliderValue * 0.004;
        }
    }
    public void carsAnimationSpeedChange(double sliderValue){
        // -100 <= sliderValue <= 100
        //
        if(sliderValue >= 0){
            carSpeed = 0.5 - sliderValue * 0.004;
        }
        else{
            carSpeed = 0.5 - sliderValue * 0.004;
        }
    }

    public void pauseAnimation(){
        synchronized (shipsAnimations){
            for(Animation a: shipsAnimations){
                a.pause();
            }
        }
        synchronized (carsAnimations){
            for(Animation a: carsAnimations){
                a.pause();
            }
        }
    }
    public void resumeAnimation(){
        synchronized (shipsAnimations) {
            for (Animation a : shipsAnimations) {
                a.play();
            }
        }
        synchronized (shipsAnimations) {
            for (Animation a : carsAnimations) {
                a.play();
            }
        }
    }
}
