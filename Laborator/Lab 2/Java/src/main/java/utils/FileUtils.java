package utils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicReference;
import java.util.function.Function;
import java.util.function.Predicate;

public class FileUtils {


    public static void createNewFile(String file, long size, int min, int max) throws IOException {
        PrintStream g = new PrintStream(file);
        g.println(size);
        for (long i = 0; i < size; i++) {
            g.printf("%d ", Math.round(Math.random() * (max-min+1)) + min);
        }
        g.close();
    }

    public static void writeToFile(String file, int n, int m, float[][] output) throws IOException {
        PrintStream g = new PrintStream(file);
        g.println(n + " " + m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                g.print(output[i][j] + " ");
            g.print('\n');
        }
        g.close();
    }

    public static void readFile(String filename, AtomicReference<float[][]> mref) throws FileNotFoundException {
        Scanner s = new Scanner(new FileInputStream(filename));
        int n = s.nextInt();
        int m = s.nextInt();

        mref.set(new float[n][]);

        float matrix[][] = mref.get();
        for (int i = 0; i < n; i++) {
            matrix[i] = new float[m];
            for (int j = 0; j < m; j++) {
                matrix[i][j] = s.nextFloat();
            }
        }
    }
}
