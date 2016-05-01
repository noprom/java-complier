package aspectj.trace.core.app;

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

    public void A1() {
        System.out.println("In A1");
        A2();
    }

    public void A2() {
        System.out.println("In A2");
    }

    public void A3() {
        System.out.println("In A3");
    }

    public void A4() {
        for (int i = 0; i < 10; i++) {
            System.out.println("In A4");
        }
    }

    public static void main(String[] args) throws IOException {
       App app = new App();
       app.A1();
    }
}