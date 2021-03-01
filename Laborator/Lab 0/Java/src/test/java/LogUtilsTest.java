import org.junit.Test;

import static org.junit.Assert.*;

public class LogUtilsTest {

    @Test
    public void sendLog() throws Exception {
        LogUtils.sendLog(0.743);
    }
}