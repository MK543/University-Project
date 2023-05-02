package com.example.promynarzece;

import javafx.animation.PathTransition;
import javafx.application.Platform;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.util.Duration;

import java.util.Arrays;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;

public class Harbour {
    final Lock carInPort;
    final Condition fullCapacity;

    int nrOfGuests;

    final Condition carLeavingShip;
    int capacity;
    int nrOfCars;


    final Lock shipInPort;
    Ship ship;

    final Condition portOccupied;
    boolean shipIn;

    final Lock waitForShip;
    final Condition waiting;

    final Condition shipLeaving;
    boolean shipGoingOut;
    final Condition shipFull;

    final Lock loadShip;
    final Condition allowLoadShip;

    final Condition allowUnloadShip;
    int currentShipCapacity;
    int currentShipSpots;
    //Animation
    boolean[] isOccupied;
    XYCoord[] harbourCircleCoords;
    double carSpeed;
    Configuration configuration;

    public Harbour(int capacity, XYCoord[] harbourCircleCoords, Configuration configuration){
        //Car's entry
        this.nrOfGuests = 0;
        this.capacity = capacity;
        this.carInPort = new ReentrantLock();
        this.fullCapacity = carInPort.newCondition();
        this.carLeavingShip = carInPort.newCondition();


        //Ship's entry
        this.shipInPort = new ReentrantLock(true);
        this.portOccupied = shipInPort.newCondition();
        this.shipIn = false;

        //Waiting for ship
        this.waitForShip = new ReentrantLock();
        this.waiting = waitForShip.newCondition();
        this.shipFull = waitForShip.newCondition();
        this.shipLeaving = waitForShip.newCondition();
        this.shipGoingOut = false;

        //Signal ship to load/unload
        this.loadShip = new ReentrantLock();
        this.allowLoadShip = loadShip.newCondition();
        this.allowUnloadShip = loadShip.newCondition();

        //Animation
        isOccupied = new boolean[capacity];
        Arrays.fill(isOccupied, false);
        this.harbourCircleCoords = harbourCircleCoords;

        this.currentShipSpots = 0;
        this.currentShipCapacity = 0;
        this.carSpeed = 0.5;
        this.configuration = configuration;
    }

    public void carEnterHarbour(String name, Car car) {
        try {
            carInPort.lock();
            while (this.nrOfCars >= this.capacity-1) {
                fullCapacity.await();
            }

            //For animation
            for(int i = 0; i< isOccupied.length-1; i++){
                Thread.sleep(1);
                if(!isOccupied[i]){
                    car.harbourXYCoord.x = harbourCircleCoords[i].x;
                    car.harbourXYCoord.y = harbourCircleCoords[i].y;
                    isOccupied[i] = true;
                    car.harbourSlot = i;
                    Path path1 = new Path();
                    MoveTo moveTo1 = new MoveTo();
                    moveTo1.setX(car.startingXYCoord.x);
                    moveTo1.setY(car.startingXYCoord.y);
                    LineTo lineTo1 = new LineTo();
                    lineTo1.setX(car.harbourXYCoord.x);
                    lineTo1.setY(car.harbourXYCoord.y);
                    path1.getElements().addAll(moveTo1, lineTo1);
                    PathTransition pathTransition1 = new PathTransition(Duration.seconds(configuration.carSpeed), path1, car.carCircle);
                    //System.out.println(carSpeed);
                    pathTransition1.setOnFinished(e -> {
                        //configuration.carsAnimations.add(path4);
                        unblock();
                        Main.animationPane.getChildren().remove(path1);
                        configuration.carsAnimations.remove(pathTransition1);
                    });

                    Platform.runLater(() -> {
                        Main.animationPane.getChildren().add(path1);
                        configuration.carsAnimations.add(pathTransition1);
                        pathTransition1.play();
                    });
                    //Thread.sleep((long) (carSpeed*1000));
                    block();
                    break;
                }
            }
            //

            nrOfCars++;

            System.out.println(name+" enters");
            System.out.println("Number of cars:" + this.nrOfCars);




        } catch (InterruptedException e) {
            //System.out.println(car.getName() + " end");
            car.repetitions = 0;
            car.shipSlot = 0;
            car.harbourSlot = 0;

        } finally {
            carInPort.unlock();
        }
    }
    public void carWaitForShip(String name, Car car) {
        try{
            //Cars await for ship's entry
            waitForShip.lock();
            while(!shipIn) {
                waiting.await();
            }

            //Cars are loaded if it's not at full capacity
            while(ship.nrOfCars == ship.capacity){
                shipFull.await();
            }

            //Ship signals that he's going set sail
            while(shipGoingOut){
                car.ship = null;
                shipLeaving.await();
            }
            car.ship = this.ship;
            System.out.println(car.getName() + " przypisany do " + car.ship.getName());
            ship.nrOfCars++;
            currentShipSpots++;

        }catch(InterruptedException e){
            //System.out.println(car.getName() + " end");
            car.repetitions = 0;
            car.shipSlot = 0;
            car.harbourSlot = 0;
        }
        finally {
            waitForShip.unlock();
        }
    }

    public void carLeaveHarbour(String name,Car car) {
        boolean hasALoadShip = false;
        try {
            carInPort.lock();
            System.out.println(name+" leaving");

            //Leaving port animation
            Path path4 = new Path();
            MoveTo moveTo4 = new MoveTo();
            moveTo4.setX(car.harbourXYCoord.x);
            moveTo4.setY(car.harbourXYCoord.y);
            LineTo lineTo4 = new LineTo();
            lineTo4.setX(car.startingXYCoord.x);
            lineTo4.setY(car.startingXYCoord.y);
            path4.getElements().addAll(moveTo4, lineTo4);
            PathTransition pathTransition4 = new PathTransition(Duration.seconds(configuration.carSpeed), path4, car.carCircle);
            pathTransition4.setOnFinished(e -> {
                unblock();
                Main.animationPane.getChildren().remove(path4);
                configuration.carsAnimations.remove(pathTransition4);
            });
            Platform.runLater(() -> {
                Main.animationPane.getChildren().add(path4);
                configuration.carsAnimations.add(pathTransition4);
                pathTransition4.play();
            });
            isOccupied[car.harbourSlot] = false;

           //car.harbourSlot = 0;
            car.harbourSlot = -1;
            block();
            //End

            this.nrOfCars--;
            System.out.println("Number of cars:" + this.nrOfCars);

            if(car.ship.nrOfCars > 0){
                carLeavingShip.signal();
            }
            else{
                loadShip.lock();
                hasALoadShip = true;

                car.ship.shipLoaded = false;
                allowUnloadShip.signal();

                loadShip.unlock();
                hasALoadShip = false;

                fullCapacity.signal();
            }

        } catch (InterruptedException e) {
            //System.out.println(car.getName() + " end");
            car.repetitions = 0;
            car.harbourSlot = 0;
            car.shipSlot = 0;

        } finally {
            if(hasALoadShip){
                loadShip.unlock();
            }
            carInPort.unlock();
        }
    }

    public void shipEnterHarbour(Ship ship){

        boolean hasTransport = false;
        boolean hasLoadShip = false;
        boolean hasWaitShip = false;
        boolean hasGiveSignal = false;
        try {

            shipInPort.lock();
            Thread.sleep(100);
            //Unload start
            System.out.println(ship.getName() + " entered harbour! " + "Passenger counter: " + ship.nr);


            //Unload animation
            Platform.runLater(() -> {
                Main.config.shipLabels[ship.id].setText("Status: Unloading");
                Main.config.shipsSquares[ship.id].setStroke(Color.BLACK);
                for(int i = 0; i<ship.capacity; i++){
                    Main.config.shipSpots[ship.id][i].setStroke(Color.BLACK);
                }
            });
            //

            ship.shipAllowLeave();
            //Waiting for unload to finish

            loadShip.lock();
            hasLoadShip = true;

            System.out.println(ship.getName() + ": Unload start!");
            while(ship.shipLoaded){
                allowUnloadShip.await();
            }
            System.out.println(ship.getName() + ": Unload finished!");

            loadShip.unlock();
            hasLoadShip = false;

            //Start load
            waitForShip.lock();
            hasWaitShip = true;

            currentShipSpots = 0;
            currentShipCapacity = ship.capacity;
            this.ship = ship;
            ship.setSail = true;
            shipIn = true;
            shipGoingOut = false;
            waiting.signalAll();
            shipLeaving.signalAll();
            shipFull.signalAll();
            waitForShip.unlock();

            hasWaitShip = false;
            ship.shipAllowEnter();

            //Load animation
            Platform.runLater(() -> {
                Main.config.shipLabels[ship.id].setText("Status: Loading");
            });
            Thread.sleep(100);
            //

            //The ship waits for a signal from at least one car and starts getting ready to leave the port
            loadShip.lock();
            hasLoadShip = true;

            while(ship.nrOfCars == 0){
                allowLoadShip.await();
            }
            loadShip.unlock();
            hasLoadShip = false;
            //Thread.sleep(100);

            ship.transport.lock();
            hasTransport = true;

            waitForShip.lock();
            hasWaitShip = true;

            shipIn = false;
            shipGoingOut = true;
            //int temp = ship.nrOfCars;
            //ship.nrOfCars = capacity;
            currentShipSpots = currentShipCapacity;
            this.ship = null;
            Thread.sleep(100);
            System.out.println(ship.getName() + ": Out");

            waitForShip.unlock();
            hasWaitShip = false;

            ship.transport.unlock();
            hasTransport = false;
            //At this point, no new cars can enter the ship.
            // The ship will wait until the last declared car is boarded

            ship.giveSignal.lock();
            hasGiveSignal = true;

            while(ship.getback){
                ship.canSail.await();
            }
            ship.giveSignal.unlock();
            hasGiveSignal = false;

            //End of load, ship set sail

            //Ship animation
            Platform.runLater(() -> {
                Main.config.shipLabels[ship.id].setText("Status: Leaving harbour");
                Main.config.shipsSquares[ship.id].setStroke(Color.RED);
                for(int i = 0; i<ship.capacity; i++){
                    Main.config.shipSpots[ship.id][i].setStroke(Color.RED);
                }
            });
            Thread.sleep(100);
            //
            System.out.println(ship.getName() + " leaving port! " + "Passenger counter: " + ship.nrOfCars);

            waitForShip.lock();
            hasWaitShip = true;

            ship.getback = true;
            ship.shipCanLeave = 0;


            waitForShip.unlock();
            hasWaitShip = false;
            //ship.nrOfCars = temp;

        }catch (InterruptedException e){
            ship.repetitions = 0;
            ship.setSail = false;
            //System.out.println(ship.getName() + " end");
        }

        finally {
            if(hasTransport){
                ship.transport.unlock();
            }
            if(hasLoadShip){
                loadShip.unlock();
            }
            if(hasWaitShip){
                waitForShip.unlock();
            }
            if(hasGiveSignal){
                ship.giveSignal.unlock();
            }
            shipInPort.unlock();
        }
    }

    public synchronized void block() throws InterruptedException {
        wait();
    }

    public synchronized void unblock() {
        notify();
    }
}