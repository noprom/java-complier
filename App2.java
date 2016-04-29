//package aspectj.trace.core.app;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * 测试应用程序
 * <p/>
 * Author: Noprom <tyee.noprom@qq.com>
 * Date: 16/3/4 下午4:38.
 */
public class App {

    public void C8() {
        System.out.println("In C8");
        for (int i = 0; i < 10; i++) {
            C10();
        }
    }

    public void C10() {
        System.out.println("In C10");
    }

    public static void main(String[] args) throws IOException {
       App app = new App();
       app.A1();
    }
}