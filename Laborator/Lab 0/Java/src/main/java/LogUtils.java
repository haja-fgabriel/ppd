import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class LogUtils {
    private final static String defaultIP = "127.0.0.1";
    private final static int defaultPort = 40000;

    public static void sendLog(double time) throws IOException {
        Socket s = new Socket(defaultIP, defaultPort);
        PrintWriter writer = new PrintWriter(s.getOutputStream());
        writer.printf("Time %f", time);
        writer.flush();
        s.close();
    }

}
