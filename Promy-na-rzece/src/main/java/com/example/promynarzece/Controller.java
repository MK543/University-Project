package com.example.promynarzece;

import javafx.animation.Animation;
import javafx.fxml.FXML;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.Button;
import javafx.scene.input.KeyEvent;

public class Controller {
    @FXML
    private Slider shipsSpeed;

    @FXML
    private Slider carsSpeed;
    @FXML
    private TextField shipsNr;
    @FXML
    private TextField carsNr;
    @FXML
    private TextField harbourCap;
    @FXML
    private TextField shipCap;

    @FXML
    private Button saveBtn;
    @FXML
    private Button startBtn;
    @FXML
    private Button stopBtn;
    @FXML
    private Button pauseResumeBtn;


    @FXML
    public void initialize(){
        startBtn.setDisable(true);
        pauseResumeBtn.setDisable(true);
        stopBtn.setDisable(true);
        carsSpeed.setDisable(true);
        shipsSpeed.setDisable(true);
    }
    @FXML
    protected void onStartButtonAction() {
        if(Main.config != null){
            Main.animationStatus = Animation.Status.RUNNING;
            Main.config.startThreads();
            startBtn.setDisable(true);
            pauseResumeBtn.setDisable(false);
            pauseResumeBtn.setText("Pause");
            stopBtn.setDisable(false);
        }
    }

    @FXML
    protected void onPauseResumeBtnAction(){
        if(Main.config != null){
            if(Main.animationStatus == Animation.Status.PAUSED){
                Main.animationStatus = Animation.Status.RUNNING;
                Main.config.resumeAnimation();
                pauseResumeBtn.setText("Pause");
                startBtn.setDisable(true);
                stopBtn.setDisable(false);
            }
            else if(Main.animationStatus == Animation.Status.RUNNING){
                Main.animationStatus = Animation.Status.PAUSED;
                Main.config.pauseAnimation();
                saveBtn.setDisable(true);
                startBtn.setDisable(true);
                pauseResumeBtn.setText("Resume");
                stopBtn.setDisable(true);
            }
        }
    }
    @FXML
    protected void onStopButtonAction() throws InterruptedException {
        if (Main.animationStatus == Animation.Status.RUNNING) {
            Main.animationStatus = Animation.Status.STOPPED;
            Main.config.interruptThreads();
            Main.animationPane.getChildren().clear();
            saveBtn.setDisable(false);
            startBtn.setDisable(true);
            pauseResumeBtn.setDisable(true);
            pauseResumeBtn.setText("Pause/Resume");
            stopBtn.setDisable(true);
            carsSpeed.setValue(0);
            shipsSpeed.setValue(0);
        }
    }

    @FXML
    protected void onSaveButtonAction() {
        try {
            int screenWidth = (int) Main.animationPane.getWidth();
            int screenHeight = (int) Main.animationPane.getHeight();
            int shipsNumber;
            int carsNumber;
            int harbourCapacity;
            int shipCapacity;
            try {
                shipsNumber = Integer.parseInt(shipsNr.getText());
            } catch (NumberFormatException e) {
                shipsNr.setText("Not a number");
                throw new DataErrorException();
            }

            try {
                carsNumber = Integer.parseInt(carsNr.getText());
            } catch (NumberFormatException e) {
                carsNr.setText("Not a number");
                throw new DataErrorException();
            }

            try {
                harbourCapacity = Integer.parseInt(harbourCap.getText());
            } catch (NumberFormatException e) {
                harbourCap.setText("Not a number");
                throw new DataErrorException();
            }

            try {
                shipCapacity = Integer.parseInt(shipCap.getText());
            } catch (NumberFormatException e) {
                shipCap.setText("Not a number");
                throw new DataErrorException();
            }

            if(shipsNumber <= 0){
                shipsNr.setText("Only positive value");
                throw new DataErrorException();
            }
            else if(carsNumber <= 0){
                carsNr.setText("Only positive value");
                throw new DataErrorException();
            }
            else if(harbourCapacity <= 1){
                harbourCap.setText("Must be greater than 1");
                throw new DataErrorException();
            }
            else if(shipCapacity <= 0){
                shipCap.setText("Only positive value");
                throw new DataErrorException();
            }

            if(shipsNumber > 1 && (shipsNumber-1)*shipCapacity+1>carsNumber){
                carsNr.setText("Car Nr > (ShipNr-1)*ShipCap");
                throw new DataErrorException();
            }

            Main.config = new Configuration(screenWidth, screenHeight, shipsNumber, carsNumber, harbourCapacity, shipCapacity);

            Main.config.prepareAnimation();
            saveBtn.setDisable(true);
            startBtn.setDisable(false);
            carsSpeed.setDisable(false);
            shipsSpeed.setDisable(false);
//            pauseBtn.setDisable(true);
//            stopBtn.setDisable(true);

        } catch (DataErrorException e1) {

        }
    }
    @FXML
    protected void onShipsSliderChanged() {
        Main.config.shipsAnimationSpeedChange(shipsSpeed.getValue());
        //System.out.println("Ships: " + shipsSpeed.getValue());
    }
    @FXML
    protected void onCarsSliderChanged() {
        Main.config.carsAnimationSpeedChange(carsSpeed.getValue());
        //System.out.println("Cars: " + carsSpeed.getValue());
    }
}

