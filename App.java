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

    public void A1() {
        System.out.println("In A1");
        A2();
        B6();
        C10();
        C9();
        C8();
    }

    public void A2() {
        System.out.println("In A2");
        A3();
        B5();
    }

    public void A3() {
        System.out.println("In A3");
        A4();
        B4();
    }

    public void A4() {
        System.out.println("In A4");
        A5();
        B3();
    }

    public void A5() {
        System.out.println("In A5");
        A6();
        B2();
    }

    public void A6() {
        System.out.println("In A6");
        A7();
        B1();
    }

    public void A7() {
        System.out.println("In A7");
        A8();
        A9();
        A10();
        B1();
        B2();
        B3();
    }

    public void A8() {
        System.out.println("In A8");
    }

    public void A9() {
        System.out.println("In A9");
    }

    public void A10() {
        System.out.println("In A10");
    }

    public void B1() {
        System.out.println("In B1");
    }

    public void B2() {
        System.out.println("In B2");
    }

    public void B3() {
        System.out.println("In B3");
    }

    public void B4() {
        System.out.println("In B4");
    }

    public void B5() {
        System.out.println("In B5");
    }

    public void B6() {
        System.out.println("In B6");
        B7();
        B7();
        C10();
    }

    public void B7() {
        System.out.println("In B7");
        B8();
        B8();
        B8();
        C9();
    }

    public void B8() {
        System.out.println("In B8");
        B9();
        C8();
    }

    public void B9() {
        System.out.println("In B9");
        B10();
        C7();
    }

    public void B10() {
        System.out.println("In B10");
        C1();
        C2();
        C3();
        C4();
        C5();
        C6();
    }

    public void C1() {
        System.out.println("In C1");
    }

    public void C2() {
        System.out.println("In C2");
        C3();
        C4();
        C5();
    }

    public void C3() {
        System.out.println("In C3");
        C4();
        C5();
    }

    public void C4() {
        System.out.println("In C4");
        C5();
    }

    public void C5() {
        System.out.println("In C5");
        C6();
        C7();
        C8();
    }

    public void C6() {
        System.out.println("In C6");
    }

    public void C7() {
        System.out.println("In C7");
    }

    public void C8() {
        System.out.println("In C8");
        for (int i = 0; i < 10; i++) {
            C10();
        }
    }

    public void C9() {
        System.out.println("In C9");
        C10();
        C10();
        C10();
    }

    public void C10() {
        System.out.println("In C10");
    }

    public static void main(String[] args) throws IOException {
       App app = new App();
       app.A1();
    }
}