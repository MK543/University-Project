package com.example.promynarzece;

import javafx.animation.PathTransition;
import javafx.animation.TranslateTransition;
import javafx.application.Platform;
import javafx.scene.shape.Circle;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;
public class Ship extends Thread{
    int nr;
    Harbour harbour;
    int capacity;
    int nrOfCars;
    int id;
    final Lock transport;
    final Condition allowEnter;
    final Condition allowLeave;
    boolean setSail;
    boolean shipLoaded;
    int repetitions;
    XYCoord[] spotsCoords;
    boolean[] isOccupied;
    boolean getback;
    int shipCanLeave;
    final Condition canSail;
    final ReentrantLock giveSignal;
    double carSpeed;

    Configuration configuration;


    public Ship(String name, int capacity, int nrOfCars, Harbour harbour, int id, int repetitions, XYCoord[] spotsCoords, Configuration configuration){
        //Data
        super(name);
        this.harbour = harbour;
        this.capacity = capacity;
        this.nrOfCars = nrOfCars;
        this.id = id;
        this.nr = 0;
        this.repetitions = repetitions;
        this.shipCanLeave = 0;

        //Synchronization
        this.transport = new ReentrantLock();
        this.allowEnter = transport.newCondition();
        this.allowLeave = transport.newCondition();
        this.setSail = true;
        this.shipLoaded = false;
        this.getback = true;
        this.giveSignal = new ReentrantLock();
        this.canSail = giveSignal.newCondition();

        //Animation
        this.spotsCoords = new XYCoord[capacity];
        System.arraycopy(spotsCoords, 0, this.spotsCoords, 0, capacity);
        this.isOccupied = new boolean[capacity];
        for(int i = 0; i<capacity; i++){
            isOccupied[i] = false;
        }
        this.carSpeed = 0.5;
        this.configuration = configuration;
    }

    public void run(){
        for(int i = 0; i< repetitions; i++){
            try {
                Thread.sleep(1);
                harbour.shipEnterHarbour(this);
            }catch (InterruptedException e){
                //System.out.println(getName() + " end");
                break;
           }
            finally {

            }
        }
        System.out.println(getName() + " Koniec");

    }
    public void carEnterShip(String name, Car car){
        boolean hasCarInPort = false;
        boolean hasLoadShip = false;
        boolean hasGiveSignal = false;

        try {
            transport.lock();

            harbour.carInPort.lock();
            hasCarInPort = true;

            Thread.sleep(1);
            //Require for animation
            for(int i = 0; i<capacity; i++){
                if(!isOccupied[i]){
                    car.shipSlot = i;
                    isOccupied[i] = true;
                    car.spotInShipXYCoord.x = spotsCoords[i].x;
                    car.spotInShipXYCoord.y = spotsCoords[i].y;

                    Path path2 = new Path();
                    MoveTo moveTo2 = new MoveTo();
                    moveTo2.setX(car.harbourXYCoord.x);
                    moveTo2.setY(car.harbourXYCoord.y);
                    LineTo lineTo2 = new LineTo();
                    lineTo2.setX(car.spotInShipXYCoord.x);
                    lineTo2.setY(car.spotInShipXYCoord.y);
                    path2.getElements().addAll(moveTo2, lineTo2);
                    PathTransition pathTransition2 = new PathTransition(Duration.seconds(configuration.shipSpeed), path2, car.carCircle);
                    pathTransition2.setOnFinished(e -> {
                        unblock();
                        Main.animationPane.getChildren().remove(path2);
                        configuration.shipsAnimations.remove(pathTransition2);
                    });
                    Platform.runLater(() -> {
                        Main.animationPane.getChildren().add(path2);
                        configuration.shipsAnimations.add(pathTransition2);
                        pathTransition2.play();
                    });
                    block();

                    harbour.isOccupied[car.harbourSlot] = false;
                    car.harbourSlot = -1;
                    break;
                }
            }
            //
            harbour.nrOfCars--;
            nr++;
            shipLoaded = true;

            harbour.loadShip.lock();
            hasLoadShip = true;

            //if(nrOfCars == 1){
            shipLoaded = true;
            harbour.allowLoadShip.signal();
            //}
            harbour.loadShip.unlock();
            hasLoadShip = false;

            harbour.fullCapacity.signal();

            giveSignal.lock();
            hasGiveSignal = true;

            shipCanLeave++;
            if(shipCanLeave == nrOfCars){
                getback = false;
                canSail.signal();
            }

            giveSignal.unlock();
            hasGiveSignal = false;

            harbour.carInPort.unlock();
            hasCarInPort = false;

            System.out.println(name + " entered " + getName());
        } catch (InterruptedException e) {
            //System.out.println(car.getName() + " end");
            car.harbourSlot = 0;
            car.shipSlot = 0;
            car.repetitions = 0;
        } finally {
            if(hasLoadShip){
                harbour.loadShip.unlock();
            }
            if(hasCarInPort){
                harbour.carInPort.unlock();
            }
            if(hasGiveSignal){
                giveSignal.unlock();
            }
            transport.unlock();
        }
    }

    public void carLeaveShip(String name, Car car){
        boolean hasCarInPort = false;
        try{
            transport.lock();
            while(setSail){
                allowLeave.await();
            }
            harbour.carInPort.lock();
            hasCarInPort = true;

            Thread.sleep(1);
            while(harbour.nrOfCars == harbour.capacity){
                harbour.carLeavingShip.await();
                hasCarInPort = false;
            }
            hasCarInPort = true;

            //Leave ship animation
            for(int i = 0; i< harbour.capacity; i++){

                if(!harbour.isOccupied[i]){

                    Path path3 = new Path();
                    MoveTo moveTo3 = new MoveTo();
                    moveTo3.setX(car.spotInShipXYCoord.x);
                    moveTo3.setY(car.spotInShipXYCoord.y);
                    LineTo lineTo3 = new LineTo();
                    lineTo3.setX(harbour.harbourCircleCoords[i].x);
                    lineTo3.setY(harbour.harbourCircleCoords[i].y);
                    path3.getElements().addAll(moveTo3, lineTo3);
                    PathTransition pathTransition3 = new PathTransition(Duration.seconds(configuration.shipSpeed), path3, car.carCircle);
                    pathTransition3.setOnFinished(e -> {
                        unblock();
                        Main.animationPane.getChildren().remove(path3);
                        configuration.shipsAnimations.remove(pathTransition3);
                    });
                    Platform.runLater(() -> {
                        Main.animationPane.getChildren().add(path3);
                        configuration.shipsAnimations.add(pathTransition3);
                        pathTransition3.play();
                    });
                    block();
                    car.harbourXYCoord.x = harbour.harbourCircleCoords[i].x;
                    car.harbourXYCoord.y = harbour.harbourCircleCoords[i].y;
                    isOccupied[car.shipSlot] = false;
                    harbour.isOccupied[i] = true;
                    car.shipSlot = -1;
                    car.harbourSlot = i;
                    break;
                }
            }
            //End

            nrOfCars--;
            harbour.nrOfCars++;

            harbour.carInPort.unlock();
            hasCarInPort = false;

            System.out.println(name + " left " + getName());

        }catch (InterruptedException e){
            //System.out.println(car.getName() + " end");
            car.harbourSlot = 0;
            car.shipSlot = 0;
            car.repetitions = 0;
        }
        finally {
            if(hasCarInPort){
                harbour.carInPort.unlock();
            }
            transport.unlock();
        }
    }

    public void shipAllowEnter(){
        try{
            transport.lock();
        }
        finally {
            transport.unlock();
        }
    }

    public void shipAllowLeave(){
        try{
            transport.lock();
            setSail = false;
            allowLeave.signalAll();
        }
        finally {
            transport.unlock();
        }
    }

    public synchronized void block() throws InterruptedException {
        wait();
    }
    public synchronized void unblock() {
        notify();
    }

}
