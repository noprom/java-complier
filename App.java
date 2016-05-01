package aspectj.trace;

import java.io.IOException;

/**
 * 测试应用程序
 * <p/>
 * Author: Noprom <tyee.noprom@qq.com>
 * Date: 16/3/4 下午4:38.
 */
public class App {
    
    /**
     * 测试标识符
     */
    public void testIdentifier() {
        int numA = 100;
        int $numB = 200;
        boolean _false = false;
    }
    
    /**
     * 测试常量
     */
    public void testConst() {
        // 1.整型常量
        int numA = 123;
        numA = 0;
        
        int numB = 0123;
        numB = 0x123;
        
        long numC = 123L;
    }
    
    public void A1() {
        System.out.println("In A1");
        A2();
    }
    
    public void A2() {
        for (int i = 0; i < 10; i++) {
            System.out.println("In A2");
        }
    }
    
    public void A3() {
        /* 测试 */
    }
    
    public static void main(String[] args) throws IOException {
        App app = new App();
        app.testIdentifier();
        app.testConst();
    }
}