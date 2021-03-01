import org.junit.Before;
import org.junit.Test;
import utils.FileUtils;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileUtilsTest {

    @Before
    public void setUp() throws IOException {
        Files.deleteIfExists(Path.of("witchdoctor.txt"));
        Files.deleteIfExists(Path.of("witchdoctor2.txt"));
        Files.deleteIfExists(Path.of("witchdoctor3.txt"));
        Files.deleteIfExists(Path.of("drakeramoray.txt"));
        FileUtils.createNewFile("witchdoctor.txt", 1000, -1000, 1000000);
        FileUtils.createNewFile("witchdoctor2.txt", 1000, -1000, 999999);
        FileUtils.createNewFile("witchdoctor3.txt", 999, -1000, 1000000);
        Files.copy(Path.of("witchdoctor.txt"), Path.of("drakeramoray.txt"));
    }

    @Test
    public void compare() throws FileNotFoundException {
    }

}
