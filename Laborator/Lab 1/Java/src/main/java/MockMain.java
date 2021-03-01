import utils.LogUtils;

import java.io.IOException;

public class MockMain {
    public static void main(String[] args) {
        try {
            LogUtils.sendLog(0.743);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
