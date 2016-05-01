package aspectj.trace;

import java.io.IOException;

/**
 * 测试应用程序
 * <p/>
 * Author: Noprom <tyee.noprom@qq.com>
 * Number: 1120132046
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
        
        // 2.实型常量
        double numD = 1.23;
        numD = 0.123;
        numD = .123;
        numD = 123.;
        numD = 123.0;
        double numE = 123e3;
        numE = 123E3;
        numE = 12.3F;
        
        // 3.布尔常量
        boolean flag = true;
        flag = false;
        
        // 4.字符串常量
        String str = "A string.";
        
        // 5.字符常量
        char ch = 'A';
    }
    
    /**
     * 测试转移字符
     */
    public void testESC() {
        String str = "aaa\'";
        str = "aaa\\";
        str = "aaa\r";
        str = "aaa\n";
        str = "aaa\f";
        str = "aaa\t";
        str = "aaa\b";
        str = "bbb\123";
        str = "ccc\u1234";
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
    
    public static void main(String[] args) throws IOException {
        App app = new App();
        app.testIdentifier();
        app.testConst();
    }
}