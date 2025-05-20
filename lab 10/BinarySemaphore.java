class BinarySemaphore {
    private final Channel<Integer> chan;

    public BinarySemaphore(boolean initialPermit) throws InterruptedException {
        this.chan = new Channel<>(1);
        if (initialPermit) {
            chan.send(1);
        }
    }

    public void acquire() throws InterruptedException {
        chan.receive();
    }

    public void release() throws InterruptedException {
        chan.send(1);
    }
}