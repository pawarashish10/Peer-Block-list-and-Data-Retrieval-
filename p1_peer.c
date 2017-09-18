/*Name - Ashish Pawar & Ankit Komawar
  Class - EECE 555
  Semester - Fall 2016*/
 
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define SERVER_PORT "8888"
//#define MAX_LINE 256
 
//function to convert char to short
 
void char2short(unsigned char* pchar, unsigned short* pshort)
{
  *pshort = (pchar[0] << 8) | pchar[1];
}
 
int main(int argc, char *argv[])
{
    struct addrinfo hints, hints1;
    struct addrinfo *result, *result1;
    
    char *host,*filename;
    unsigned char req,breq,blkreq,flszreq;
    unsigned char ureq,bureq,uflszreq;
    unsigned char *req_ptr, *breq_ptr,*blkreq_ptr, *flszreq_ptr;
    unsigned char server_reply[40000],server_reply1[40000],server_reply2[40000],server_reply3[200]; 
    int s,s1, sckt,sckt1;
    int x,swp;
    req=0x00;
    breq=0x02;
    blkreq=0x04;
    flszreq=0x07;
    ureq = (char)req;
    bureq = (char)breq;
    uflszreq = (char)flszreq;
    req_ptr = &ureq; 
    breq_ptr = &bureq;
    blkreq_ptr = (unsigned char *) malloc (5);
    *blkreq_ptr = (unsigned char)blkreq;
    flszreq_ptr = &uflszreq;
    if (argc==3)
    {
        host = argv[1];
        filename = argv[2];
    }
    else
    {
        fprintf(stderr, "usage: %s host\n", argv[0]);
        exit(1);
    }
 
    /* Translate host name into peer's IP address */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
  
    if ((s = getaddrinfo(host, SERVER_PORT, &hints, &result)) != 0 )
    {
        fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
        exit(1);
    }
  
    //create socket
    sckt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
     if (sckt == -1)
    {
            printf("Could not create socket");
        }
    else
    {
        //puts("Socket created");
    }
  
    //connect to port
        if (connect(sckt, result->ai_addr, result->ai_addrlen) < 0)
        {
            perror("connect failed. Error");
            return 1;
        }
        else
        {
        //puts("connection success");
        }
  
    //send 1 byte 0x00 msg to server       
    x = send(sckt , req_ptr , 1, 0); 
    if(  x < 0)
    {
      printf("\nerr no-->%d", x);
          puts("Send failed");
          return 1;
    }
    else
    {
    //puts("send success");
    }  
   
    //Receive a reply from the server
    x = recv(sckt , server_reply , 40000 , 0);
    if( x < 0)
    {
          printf("\nerr no-->%d", x);
          puts("recv failed");
          return 1;
       
    }
    else
    {
    //puts("recv success");
    }
  
    freeaddrinfo(result);
    close(s);
    close(sckt);
  
    // For array size
   unsigned short int  no_peer =0;
   memcpy(&no_peer,server_reply+1,1);
  
    unsigned short int  array2[20*32767][3], array3[20*32767][3], array4[32767][3]; 
    // for file size
 
    if ((s = getaddrinfo(host, SERVER_PORT, &hints, &result)) != 0 )
    {
        fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
        exit(1);
    }
  
  
    //create socket
    sckt = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
     if (sckt == -1)
        {
            printf("Could not create socket");
        }
    else
    {
            //puts("Socket created");
    }
  
    //connect to port
    if (connect(sckt, result->ai_addr, result->ai_addrlen) < 0)
    {
            perror("connect failed. Error");
            return 1;
    }
    else
    {
        //puts("connection success");
    }
  
    //send 1 byte 0x00 msg to server       
    x = send(sckt , flszreq_ptr , 1, 0); 
    if(  x < 0)
    {
      printf("\nerr no-->%d", x);
          puts("Send failed");
          return 1;
    }
    else
    {
    //puts("send success");
    }  
   
    //Receive a reply from the server
    x = recv(sckt , server_reply3 , 200 , 0);
    if( x < 0)
    {
          printf("\nerr no-->%d", x);
          puts("recv failed");
          return 1;
       
    }
    else
    {
       //puts("fl recv success");
    }
  
    freeaddrinfo(result);
    close(s);
    close(sckt);
 
    //convert received data to presentable form
    int z = server_reply[1];
    int size= (z*6)+2;
    char str[size];
    unsigned char *port;
    int i,a,b,j,k;
    unsigned short int v;
    port = (unsigned char *) malloc ( size + 1 );  
    struct sockaddr_in addr_cli;
    v = 0;
    a = 0;
    for(i=2 ; i<size; i=i+6)
    {
        memcpy(&(addr_cli.sin_addr),server_reply + i,6);
        inet_ntop(AF_INET, &(addr_cli.sin_addr), str, INET_ADDRSTRLEN);
        //printf("\n%s", str);
        memcpy(port,server_reply + i +4,2);
        unsigned short p;
        char2short(port,&p);
        //printf(":%d",p);
        char port1[20];
        sprintf(port1,"%d",p);
        memset(&hints1, 0, sizeof(hints1));
        hints1.ai_family = AF_INET;
        hints1.ai_socktype = SOCK_STREAM;
        hints1.ai_flags = 0;
        hints1.ai_protocol = 0;
  
        if ((s1 = getaddrinfo(str, port1, &hints1, &result1)) != 0 )
        {
            fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s1));
            exit(1);
        }
    sckt1 = socket(result1->ai_family, result1->ai_socktype, result1->ai_protocol);
        if (sckt1 == -1)
        {
            printf("Could not create socket");
        }
        else
        {
            //puts("Socket created");
        }
  
    //connect to port
        if (connect(sckt1, result1->ai_addr, result1->ai_addrlen) < 0)
        {
            perror("connect failed. Error");
            return 1;
        }
        else
        {
            //puts("connection success");
        }
 
        x = send(sckt1 , breq_ptr , 1, 0); 
        if(  x < 0)
        {
          printf("\nerr no-->%d", x);
              puts("Send failed");
            return 1;
        }
        else
        {
        //puts("send success");
    }  
   
        //Receive a reply from the server
        x = recv(sckt1 , server_reply1 , 40000 , 0);
        if( x < 0)
        {
              printf("\nerr no-->%d", x);
              puts("recv failed");
              return 1;
       
        }
        else
        {
        //puts("recv success");
        }
  
 
        freeaddrinfo(result1);
        close(s1);
        close(sckt1);
  
        unsigned short int x,y,strt,end,strt1,end1;
        int counter;
        memcpy(&x,server_reply1+1,2);
        y = ntohs(x);
        counter = (y*4)+3;  
       for(j=3; j<counter ; j=j+4)
    {
            memcpy(&strt,server_reply1+j,2);
            strt1 = ntohs(strt);
            array2[a][0] = v;
            array2[a][1] = strt1;
            memcpy(&end,server_reply1+j+2,2);
            end1 = ntohs(end);
            array2[a][2] = end1;
            a++;
     
      }
          v++;
  }
 
    j = 1;
    for (i = 0; i < a; ++i)
    {
        for (k = i + 1; k < a; ++k)
        {
            if (array2[i][j] > array2[k][j])
            {
                  swp = array2[i][j];
                array2[i][j] = array2[k][j];
                array2[k][j] = swp;
        swp = array2[i][j-1];
                array2[i][j-1] = array2[k][j-1];
                array2[k][j-1] = swp;
                swp = array2[i][j+1];
                array2[i][j+1] = array2[k][j+1];
                array2[k][j+1] = swp;
            }
          
        }
      
    }
  
    j = 2;
    for (i = 0; i < a; ++i)
    {
        for (k = i + 1; k < a; ++k)
        {
        if (array2[i][j] > array2[k][j]  && array2[i][j-1] == array2[k][j-1])
            {
                swp = array2[i][j];
                array2[i][j] = array2[k][j];
                array2[k][j] = swp;
                swp = array2[i][j-1];
                array2[i][j-1] = array2[k][j-1];
                array2[k][j-1] = swp;
                swp = array2[i][j-2];
                array2[i][j-2] = array2[k][j-2];
                array2[k][j-2] = swp;
            }
        }
    }
  
   k =0;
   for (i = 0; i < a; ++i)
   {
       if(array2[i][1]!=array2[i+1][1])
       {
           array3[k][0] = array2[i][0];
           array3[k][1] = array2[i][1];
           array3[k][2] = array2[i][2];
           k++;
         
       }
    }
  
   
    int fill_counter = 0;
    array4[0][0]=array3[0][0];
    array4[0][1]=array3[0][1];
    array4[0][2]=array3[0][2];
    fill_counter = array3[0][2];
    b=1;
    for (i = 0; i < a; ++i)
    {          
    if(array3[i][2] > fill_counter && array3[i][1] <= fill_counter+1 )
    {  
       array4[b][0]=array3[i][0];
       array4[b][1]=fill_counter+1;
       array4[b][2]=array3[i][2];
       fill_counter =  array3[i][2];
       b++;
    }
    }
  
        for(i=0 ; i<b; i++)
    {
        int inc;
        inc = (array4[i][0]*6)+2;
        memcpy(&(addr_cli.sin_addr),server_reply + inc,6);
        inet_ntop(AF_INET, &(addr_cli.sin_addr), str, INET_ADDRSTRLEN);
        memcpy(port,server_reply + inc +4,2);
        unsigned short p;
        char2short(port,&p);
        char port1[20];
        sprintf(port1,"%d",p);
        memset(&hints1, 0, sizeof(hints1));
      
        hints1.ai_family = AF_INET;
        hints1.ai_socktype = SOCK_STREAM;
        hints1.ai_flags = 0;
        hints1.ai_protocol = 0;
  
        if ((s1 = getaddrinfo(str, port1, &hints1, &result1)) != 0 )
        {
            fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s1));
            exit(1);
        }
        sckt1 = socket(result1->ai_family, result1->ai_socktype, result1->ai_protocol);
        if (sckt1 == -1)
        {
            printf("Could not create socket");
        }
        else
        {
            // puts("\nSocket created");
        }
  
    //connect to port
        if (connect(sckt1, result1->ai_addr, result1->ai_addrlen) < 0)
        {
            perror("connect failed. Error");
            return 1;
        }
        else
        {
            // puts("connection success");
        }
        int short *start_blk;
        start_blk = (short int *)malloc(2);
        *start_blk= htons(array4[i][1]);
        int short *end_blk;
        end_blk = (short int *)malloc(2);
        *end_blk = htons(array4[i][2]);
        memcpy(blkreq_ptr+1,start_blk,2);
        memcpy(blkreq_ptr+3,end_blk,2);
   
        x = send(sckt1 , blkreq_ptr , 5, 0); 
        if(  x < 0)
        {
             printf("\nerr no-->%d", x);
         puts("Send failed");
             return 1;
        }
        else
        {
           //  puts("send success");
        }  
   
        x = recv(sckt1 , server_reply2 , 32767 , 0);
        if( x < 0)
        {
              printf("\nerr no-->%d", x);
              puts("recv failed");
              return 1;
       
        }
        else
        {
 
           // puts("recv success");
        }
  
        freeaddrinfo(result1);
        close(s1);
        close(sckt1);
        char *temp,*temp1;
        int diff,diff1;
        if(i == b-1)
    {
        int sze,l_sze;
        memcpy(&sze,server_reply3+1,4);
    sze = ntohl(sze);
        l_sze = (sze % 2048);
        diff1 = ((array4[i][2]-array4[i][1])*2048) + l_sze;
        temp1 = (char *)malloc(diff1);
        memcpy(temp1,server_reply2+1,diff1);
        FILE *fp;
        fp = fopen(filename, "a+");
        fwrite(temp1,1,diff1,fp);     
        fclose(fp);
      
    }
    else
    {
        diff = (array4[i][2]-array4[i][1])+1;
        temp = (char *)malloc(diff*2048);
        memcpy(temp,server_reply2+1,diff*2048);
        FILE *fp;
        fp = fopen(filename, "a+");
        fwrite(temp,1,diff*2048,fp);         
        fclose(fp);
    }
      
   }
 
    return 0;
}
