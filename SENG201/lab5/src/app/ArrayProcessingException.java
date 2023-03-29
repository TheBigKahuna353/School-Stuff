package app;

class ArrayProcessingException extends Exception {

    public ArrayProcessingException() {
      super();
    }

    public ArrayProcessingException(String message) {
      super(message);
    }

    public ArrayProcessingException(Throwable cause) {
      super(cause);
    }
}