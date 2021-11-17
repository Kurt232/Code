package com.company;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) throws IOException {
        TCPServer server=new TCPServer();
        server.Service();
    }
}

class TCPServer {
    private int port = 8008;
    private ServerSocket serverSocket;

    public TCPServer() throws IOException {
        serverSocket = new ServerSocket(port);
        System.out.println("server listening " + port + " port, and wait for connection");
    }

    private PrintWriter getWriter(Socket socket) throws IOException{
        //获得输出流缓冲区的地址
        OutputStream socketOut=socket.getOutputStream();
        //网络流写出需要使用flush，这里在printWriter构造方法直接设置为自动flush
        return new PrintWriter(new OutputStreamWriter(socketOut,"utf-8"),true);
    }

    private BufferedReader getReader(Socket socket) throws IOException{
        //获得输入流缓冲区的地址
        InputStream socketIn=socket.getInputStream();
        return new BufferedReader(new InputStreamReader(socketIn,"utf-8"));
    }

    //单客户版本，每次只能与一个用户建立通信连接
    public void Service(){
        while (true){
            Socket socket=null;
            try {
                //此处程序阻塞，监听并等待用户发起连接，有连接请求就生成一个套接字
                socket=serverSocket.accept();

                //本地服务器控制台显示客户连接的用户信息
                System.out.println("New connection accepted:"+socket.getInetAddress());
                BufferedReader br=getReader(socket);//字符串输入流
                PrintWriter pw=getWriter(socket);//字符串输出流
                pw.println("S: Welcome!");

                String msg=null;
                //此处程序阻塞，每次从输入流中读入一行字符串
                while ((msg=br.readLine())!=null){
                    //C: ”bye“, close connection
                    if(msg.equals("bye")){
                        pw.println("S: close the connect!");
                        System.out.println("the client close the connection!");
                        break;
                    }
                    //发送client 信息的长度
                    pw.println("the length of massage form client: "+msg.length());
                }
            }catch (IOException e){
                e.printStackTrace();
            }finally {
                try {
                    if (socket!=null)
                        socket.close();//关闭socket连接以及相关的输入输出流
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }
    }
}
