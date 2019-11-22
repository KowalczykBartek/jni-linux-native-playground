public class Main {
    public static void main(String[] args) throws InterruptedException {
        Socket socket = Socket.of("127.0.0.1", 8080);
        socket.connect();

        while (true) {
            byte[] data = socket.read0();
            System.out.println(new String(data));
            Thread.sleep(1000);
        }
    }
}