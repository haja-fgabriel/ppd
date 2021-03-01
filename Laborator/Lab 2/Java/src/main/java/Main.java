import utils.FileUtils;
import utils.LogUtils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicReference;


public class Main {
    private static float input[][];
    private static float kernel[][];
    private static int n;
    private static int m;
    private static int numThreads;

    public static void main(String[] args) throws IOException, InterruptedException {
        if (args.length < 2) {
            System.err.println("Arguments: <input_file> <kernel_input_file> [--log-to-socket]");
            return;
        }


        AtomicReference<float[][]> inputRef = new AtomicReference<>(input);
        AtomicReference<float[][]> kernelRef = new AtomicReference<>(kernel);

        FileUtils.readFile(args[0], inputRef);
        FileUtils.readFile(args[1], kernelRef);

        input = inputRef.get();
        kernel = kernelRef.get();
        n = input.length;
        m = input[0].length;

        long tBegin = System.currentTimeMillis();
        (new MatrixTransformer(input, kernel, n, m, 0, n*m, null)).run();
        long tEnd = System.currentTimeMillis();

        FileUtils.writeToFile("output.txt", n, m, input);

        System.out.println("[DEBUG] Time: " + (double)(tEnd-tBegin)/1000);

        if (args.length >= 3 && args[2].equals("--log-to-socket")) {
            try {
                LogUtils.sendLog((double)(tEnd-tBegin)/1000);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
