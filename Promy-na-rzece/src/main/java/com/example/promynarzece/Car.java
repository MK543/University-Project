package com.example.promynarzece;
//import javafx.animation.PathTransition;
import javafx.animation.ScaleTransition;
import javafx.application.Platform;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
/*import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;*/
import javafx.util.Duration;

import java.util.Random;
public class Car extends Thread{
    Ship ship;
    Harbour harbour;
    Random random;
    int repetitions;

    int harbourSlot;
    int shipSlot;
    Circle carCircle;
    Paint paint;

    ScaleTransition transition;
    ScaleTransition transition2;
    XYCoord startingXYCoord;

    XYCoord harbourXYCoord;

    XYCoord spotInShipXYCoord;
    public Car(Harbour harbour, String name, int repetitions, int id, Circle carCircle, XYCoord startingXYCoord){
        super(name);
        this.harbour = harbour;
        this.random = new Random();
        this.ship = null;
        this.repetitions = repetitions;
        this.paint = Color.color(Math.random()%255,Math.random()%255,Math.random()%255);
        this.carCircle = carCircle;
        this.harbourSlot = 0;
        this.shipSlot = 0;
        this.startingXYCoord = startingXYCoord;
        this.harbourXYCoord = new XYCoord();
        this.spotInShipXYCoord = new XYCoord();

        //Appear
        this.transition = new ScaleTransition();  // create a scale transition
        this.transition.setDuration(Duration.seconds(0.3));  // set the duration to 1 second
        this.transition.setNode(carCircle);  // set the node (i.e. the circle) to animate
        this.transition.setToX(1);  // set the final x scale of the circle to 1 (fully visible)
        this.transition.setToY(1);  // set the final y scale of the circle to 1 (fully visible)

        //Disappear
        this.transition2 = new ScaleTransition();  // create a scale transition
        this.transition2.setDuration(Duration.seconds(0.3));  // set the duration to 1 second
        this.transition2.setNode(carCircle);  // set the node (i.e. the circle) to animate
        this.transition2.setToX(0);  // set the final x scale of the circle to 1 (fully visible)
        this.transition2.setToY(0);  // set the final y scale of the circle to 1 (fully visible)
    }
    public void run(){

        for(int i = 0; i<repetitions; i++){
                try {

                    //Appearance animation
                    transition.setOnFinished(e -> {
                        unblock();
                    });
                    Platform.runLater(() -> {
                        transition.play();  // play the animation
                    });
                    block();

                    //End

                    harbour.carEnterHarbour(getName(), this);

                    harbour.carWaitForShip(getName(), this);

                    ship.carEnterShip(getName(), this);

                    ship.carLeaveShip(getName(), this);
                    Thread.sleep(100);
                    harbour.carLeaveHarbour(getName(), this);

                    //Disappearance animation
                    transition2.setOnFinished(e -> {
                        unblock();
                    });
                    Platform.runLater(() -> {
                        transition2.play();  // play the animation
                    });
                    block();
                    //End

                }catch (InterruptedException e){
                    shipSlot = 0;
                    harbourSlot = 0;
                    //System.out.println(getName() + " end");
                    break;
                }
                finally {

                }


        }
        System.out.println(getName() + " Koniec");
    }

    public synchronized void block() throws InterruptedException {
        wait();
    }

    public synchronized void unblock() {
        notify();
    }
}