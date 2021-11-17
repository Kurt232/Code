package com.company;

import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) throws IOException {
        UDPServer server=new UDPServer();
        server.Service();
    }
}

class UDPServer {
    private final int port = 8888;
    DatagramSocket serverSocket;
    DatagramPacket receivePacket;
    int MAX_PACKET_SIZE=1024;

    private DatagramPacket receive() throws IOException{
        DatagramPacket UDPReceive;
        byte[] data=new byte[MAX_PACKET_SIZE];
        UDPReceive=new DatagramPacket(data, data.length);
        serverSocket.receive(UDPReceive);
        return UDPReceive;
    }

    private void send(String msg, InetAddress direIp, Integer direPort) throws IOException{
        DatagramPacket sendPacket;
        byte[] data=msg.getBytes();
        sendPacket =new DatagramPacket(data, data.length, direIp, direPort);
        serverSocket.send(sendPacket);
    }

    public void Service() throws IOException{
        try{
            serverSocket=new DatagramSocket(port);
            System.out.println("the service is running on port: "+serverSocket.getLocalPort());

            while(true){
                String msg=null;
                receivePacket=receive();
                InetAddress sourIp=receivePacket.getAddress();
                Integer sourPort=receivePacket.getPort();
                msg = new String(receivePacket.getData(), 0, receivePacket.getLength(), "utf-8");

                if(msg.equalsIgnoreCase("bye")) {
                    send("S: you finished the service, bye!", sourIp, sourPort);
                    System.out.println(receivePacket.getSocketAddress() + " finished the service ");
                    continue;
                }

                System.out.println("service beginning for: "+ receivePacket.getSocketAddress());

                StringBuilder sendData= new StringBuilder(msg);
                //reverse the string
                sendData.reverse();
                send("your msg be reversed: "+sendData, sourIp, sourPort);
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
