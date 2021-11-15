package com.company;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException {
        /*
        无线局域网适配器 WLAN:
        连接特定的 DNS 后缀 . . . . . . . :
        本地链接 IPv6 地址. . . . . . . . : fe80::4c29:fe1f:1e7a:157c%17
        IPv4 地址 . . . . . . . . . . . . : 192.168.3.25
        子网掩码  . . . . . . . . . . . . : 255.255.255.0
        默认网关. . . . . . . . . . . . . : 192.168.3.1
        */
        TCPClient client=new TCPClient("192.168.3.25", "8008");
        System.out.println(client.receive());
        System.out.println("hello");
        client.send("hello");
        System.out.println(client.receive());
        client.send("bye");
        System.out.println(client.receive());
    }
}

class TCPClient{
    private Socket socket;

    private PrintWriter pw;
    private BufferedReader br;

    public TCPClient(String ip, String port) throws IOException {
        //主动向服务器发起连接，实现TCP三次握手
        //不成功则抛出错误，由调用者处理错误
        socket =new Socket(ip,Integer.parseInt(port));

        //得到网络流输出字节流地址，并封装成网络输出字符流
        OutputStream socketOut=socket.getOutputStream();
        //参数true表示自动flush数据
        pw=new PrintWriter(new OutputStreamWriter(socketOut,"utf-8"),true);

        //得到网络输入字节流地址，并封装成网络输入字符流
        InputStream socketIn=socket.getInputStream();
        br=new BufferedReader(new InputStreamReader(socketIn,"utf-8"));
    }

    public void send(String msg){
        //输出字符流，由socket调用系统底层函数，经网卡发送字节流
        pw.println(msg);
    }

    public String receive(){
        String msg=null;
        try {
            //从网络输入字符流中读取信息，每次只能接受一行信息
            //不够一行时（无行结束符），该语句阻塞
            //直到条件满足，程序往下运行
            msg=br.readLine();
        }catch (IOException e){
            e.printStackTrace();
        }
        return msg;
    }
    public void close(){
        try {
            if (socket!=null)
                socket.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
