package examples;

import linux.TunTap;

public class TunTapTest {
    public static void main(String... args) throws InterruptedException {
        TunTap tunTap = new TunTap();
        int tunFd = tunTap.tun_alloc();

        System.out.println("Tun/tap fd " + tunFd);

        while(true) {
            byte[] packet = tunTap.read0();
            for(int i = 0; i < packet.length; i++) {
                System.out.print(String.format("0x%08X",packet[i]) + " ");
            }

            System.out.println();
            Thread.sleep(1000);
        }
    }
}
