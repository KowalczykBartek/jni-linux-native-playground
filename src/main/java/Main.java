public class Main {
    public static void main(String[] args) throws InterruptedException {
        Socket socket = Socket.of("127.0.0.1", 8080);
        socket.connect();

        byte[] data = socket.read0();
        System.out.println(new String(data));

        while (true) {
            Thread.sleep(1000);
            socket.write0(data);
        }
    }
}