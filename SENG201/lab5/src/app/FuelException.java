package app;

public class FuelException extends IllegalStateException {
    
    public FuelException(String message) {
        super(message);
    }

    public FuelException() {
        super();
    }
}
