module com.example.promynarzece {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.promynarzece to javafx.fxml;
    exports com.example.promynarzece;
}