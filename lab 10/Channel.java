import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

class Channel<T> {
    private final BlockingQueue<T> queue;

    public Channel(int capacity) {
        this.queue = new LinkedBlockingQueue<>(capacity);
    }

    public void send(T msg) throws InterruptedException {
        queue.put(msg);
    }

    public T receive() throws InterruptedException {
        return queue.take();
    }

    public T receive(long timeout, TimeUnit unit) throws InterruptedException {
        return queue.poll(timeout, unit);
    }
}