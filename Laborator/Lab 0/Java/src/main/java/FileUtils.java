import com.sun.tools.javac.util.Pair;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.function.Function;
import java.util.function.Predicate;

public class FileUtils {

    private static boolean compare(Path a, Path b, Function<Pair<Scanner, Scanner>, Boolean> comparer) throws FileNotFoundException {
        long n, m;
        int x, y;
        Scanner f1 = new Scanner(new FileInputStream(a.toFile()));
        Scanner f2 = new Scanner(new FileInputStream(b.toFile()));
        n = f1.nextLong();
        m = f2.nextLong();

        if (n != m) {
            f1.close();
            f2.close();
            return false;
        }

        for (long i = 0; i < n; i++) {
            if (!comparer.apply(Pair.of(f1, f2)))
                return false;
        }

        f1.close();
        f2.close();
        return true;
    }


    public static boolean compareInts(Path a, Path b) throws FileNotFoundException {
        return compare(a, b, p -> p.fst.nextInt() == p.snd.nextInt());
    }

    public static boolean compareDoubles(Path a, Path b) throws FileNotFoundException {
        return compare(a, b, p -> p.fst.nextDouble() == p.snd.nextDouble());
    }

    public static void createNewFile(Path file, long size, int min, int max) throws IOException {
        PrintStream g = new PrintStream(file.toFile());
        g.println(size);
        for (long i = 0; i < size; i++) {
            g.printf("%d ", Math.round(Math.random() * (max-min+1)) + min);
        }
        g.close();
    }

}
