package com.company;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException {
        /*
        2021.11.17 20:40
        无线局域网适配器 WLAN:
        连接特定的 DNS 后缀 . . . . . . . :
        本地链接 IPv6 地址. . . . . . . . : fe80::4c29:fe1f:1e7a:157c%17
        IPv4 地址 . . . . . . . . . . . . : 10.133.131.187
        子网掩码  . . . . . . . . . . . . : 255.255.240.0
        默认网关. . . . . . . . . . . . . : fe80::5a69:6cff:fe4c:4753%17
                                           10.133.128.1
        */
        UDPClient client=new UDPClient("10.133.131.187", "8888");
        System.out.println("send: hello");
        client.send("hello");
        System.out.println(client.receive());
        client.send("bye");
        System.out.println(client.receive());
        client.close();
    }
}

class UDPClient{
    private InetAddress direIP;
    private Integer direPort;
    DatagramSocket clientSocket;
    int MAX_PACKET_SIZE=1024;//max receive

    public UDPClient(String direIP, String direPort) throws IOException{
        this.direIP = InetAddress.getByName(direIP);
        this.direPort = Integer.parseInt(direPort);
        this.clientSocket = new DatagramSocket();
    }

    //send
    public void send(String msg){
        try {
            //convert string to byte[]
            byte[] outData=msg.getBytes("utf-8");
            //DatagramPacket
            DatagramPacket outPacket=new DatagramPacket(outData,outData.length,direIP,direPort);
            //send datagramPacket
            clientSocket.send(outPacket);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public String receive(){
        String msg;

        DatagramPacket inPacket=new DatagramPacket(new byte[MAX_PACKET_SIZE],MAX_PACKET_SIZE);
        try {
            clientSocket.receive(inPacket);
            msg=new String(inPacket.getData(),0,inPacket.getLength(),"utf-8");
        } catch (IOException e) {
            e.printStackTrace();
            msg=null;
        }
        return msg;
    }

    public void close(){
        //check!
        if (clientSocket!=null)
            clientSocket.close();
    }
}

