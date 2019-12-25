import requests
from lxml import etree
import json
import re
from bs4 import BeautifulSoup
import sys
import time

def setting_aquire():
    with open("settings.json",'rb') as f:
        data=json.load(f)
    return data

def translation(part):
    part_dic={'edu':"教育",'ent':"娱乐",'sports':"体育",'fashion':"时尚",'tech':"科技",
        'politics':"政治",'finance':"财经",'military':"军事",'legal':"法制",'leaders':"领导",'tzgg':"通知公告",
        'travel':"旅游",'gjjl':"国际交流",'sjjx':"实践教学",'jwyx':"教务学籍"}
    return part_dic[part]

def date_form_RM(_date):
    #"2019/1128"获取正确的日期格式
    return _date[0:4]+'-'+_date[5:7]+'-'+_date[7:]

def RMspider(headers, NewsDic, data):
    choice=[]
    config = data["人民网"]
    for i in ["政治", "财经", "军事", "法制", "领导"]:
        choice.append(config[i])

    #choice 选择列表，与下列表对应，1选中，0未选中
    part_list1 = ["politics", "finance", "military","legal", "leaders"] # 待选择板块
    chooselist = []

    j = 0
    for i in part_list1:
        if choice[j] == 1:
            chooselist.append(i)
        j=j+1
    # print(chooselist)
    resultdic={}
    url1 = ".people.com.cn/index"
    for part in chooselist:                  #模块循环
        url2 = "http://" + part + url1
        resultdic[translation(part)] = []
        for page in range(1,2):              #页码循环
            url = url2 + str(page) + ".html"
            response = requests.get(url, headers=headers).content.decode("gb2312","ignore")
            html = etree.HTML(response)
            title_result = html.xpath('//div[@class="on"]/h5/a')
            link_result = html.xpath('//div[@class="on"]/h5/a/@href')
            content_result = html.xpath('//div[@class="on"]/em/a')
            for i in range(len(title_result)):
                temp = []     #[title, date, content, link]
                temp.append(title_result[i].text)
                temp.append(date_form_RM(re.findall(r'/n1/(.*?)/c', link_result[i])[0]))
                if str(content_result[i].text) == 'None':
                    temp.append('')
                else :
                    temp.append(str(content_result[i].text).replace('\t','').replace('\xa0',''))
                if 'v.people.cn' in link_result[i]:
                    temp.append(link_result[i])
                else:
                    temp.append(url+link_result[i])
                resultdic[translation(part)].append(temp)
    NewsDic['人民网'] = resultdic
    return        

def date_form_WY(_date):
    #获取正确的日期格式
    return '20'+_date[0:2]+'-'+_date[3:5]+'-'+_date[5:]

def abstract_WY(headers, url):
    #提取注释
    response = requests.get(url,headers=headers).content.decode("gbk","ignore")
    soup = BeautifulSoup(response,'html.parser')
    res1  = str(soup.find_all('div',class_="post_text"))
    res1 = re.sub(r'<.*?>' ,'',res1)
    res1 = re.sub(r'[\s\[\]\'\'\(\)\{\}\"\"\.\:\;]' ,'',res1)
    s1 = "window.NTES&&functiondvarf=functioncvarb=c.getAttributeflashvars,a=c.getAttributerepovideourl.replace.flv,-mobile.mp4;h=dc.parentNode.parentNode.parentNode,g=;if1/*iPhone|iPad|iPod|Android|NETEASEBOBO|blackberry|bbd+/ig.testnavigator.userAgent*/g=您的浏览器暂时无法播放此视频.;NTES.video-inner.video.attrstyle,background:#000;;h.$.video0.innerHTML=g;,e=functionbvara=db.parentNode.parentNode.parentNode;a.$li.removeCsson,b.addCsson,a.$.video-title0.innerHTML=string==typeofb.textContent?b.textContent:b.innerText,a.$.video-title0.setAttributehref,b.getAttributeurl,a.$.video-from0.innerHTML=（来源：+b.getAttributesource+）,fb;;window.continuePlay=functionvara,b=dd.video-list.on0.nextSibling;3==b.nodeType&&b=db.nextSibling;ifb&&d.video-innerinput0.checkedeb;,functionvara=init:functionifd.video-listli0dd.video-listli0.addCsson,this.eventBind;,eventBind:functiond.video-listli.addEventclick,functionbedthis,b.preventDefault;;;a.init;;NTES;"
    res1 = re.sub(s1 ,'',res1)
    s1 = "#endTextvideo-infoatext-decorationnonecolor#000"
    if s1 in res1:
        res1=''
    # res1 = re.sub(s1 ,'',res1)
    
    if len(res1) > 100:
        return res1[0:100]+'...'
    else:
        return res1

def WYspider(headers, NewsDic, data):
    choice=[]
    config = data["网易"]
    for i in ["旅游", "娱乐", "体育", "教育", "科技"]:
        choice.append(config[i])

    #choice 选择列表，与下列表对应，1选中，0未选中edu tech
    part_list1 = ["travel", "ent", "sports", "edu", "tech"] # 待选择板块
    chooselist = []
    j = 0
    for i in part_list1:
        if choice[j] == 1:
            chooselist.append(i)
        j=j+1
    # print(chooselist)
    resultdic={}
    #{part:[[title,time,content,link]]}
    date_pat = '.163.com/(.*?)/[0-9][0-9]/'

    for part in chooselist:
        resultdic[translation(part)]=[]

        url2 = 'http://news.163.com/special/0001386F/rank_'+part+'.html'
        response = requests.get(url2,headers=headers).content.decode("gbk","ignore")
        html = etree.HTML(response)
        url_result = html.xpath("//tr/td/a/@href")
        title_result = html.xpath("//tr/td/a")
        if len(title_result) <= 20:
            num_to_get = len(title_result)
        else:
            num_to_get = 20
        for i in range(num_to_get):
            temp = []
            temp.append(title_result[i].text)
            temp.append(date_form_WY(re.findall(date_pat,url_result[i])[0]))#把正确的日期找出，格式化，然后放入列表
            temp.append(abstract_WY(headers,url_result[i]))
            temp.append(url_result[i])
            resultdic[translation(part)].append(temp)
    NewsDic['网易'] = resultdic
    return

def date_form_XL(txt):
    if re.findall(r'/([-0-9]+)/',txt) != []:
        return re.findall(r'/([-0-9]+)/',txt)[0]
    else:
        return '最近'

def absrtact_XL(url):
    response = requests.get(url,headers=headers).content.decode("utf-8","ignore")
    response = requests.get(url,headers=headers).content.decode("utf-8","ignore")
    soup = BeautifulSoup(response,'html.parser')
    res1 = str(soup.find_all('div',class_="article"))
    res1 = re.sub(r'<.*?>' ,'',res1)
    # res1 = re.sub(r'<div.*?>' ,'',res1)
    res1 = re.sub(r'[\t\n\[\]\'\'\{\}\(\)\"\\]' ,'',res1)
    s1 = r"window.sina_survey_config =     surveyCss: true,               //调查问答样式true, false, http （不使用默认样式配置false或者不传此参数）    resultCss: true,               //调查结果样式true, false, http （不使用默认样式配置false或者不传此参数）    source: vote               //通过来源设置图片宽高 sina手浪, vote默认"
    res1 = re.sub(s1 ,'',res1)
    s1 = "                      function                        var adScript = document.createElementscript;                        adScript.src = //d1.sina.com.cn/litong/zhitou/sinaads/demo/changwy/link/yl_left_hzh_20160119.js;                        document.getElementsByTagNamehead0.appendChildadScript;                        ;                    "
    res1 = re.sub(s1 ,'',res1)
    if len(re.findall(r"[\u4e00-\u9fa5]",res1[0:100])) <=10:
        res1=''
    if "SinaPage.loadWidget    trigger:" in res1:
        res1=''
    if len(res1) > 100:
        return '<P>'+res1[0:100]+'...'+'</p>'
    else:
        return '<P>'+res1+'</p>'

def XLspider(headers, NewsDic, data):
    config = data["新浪"]
    choice=[]
    for i in ["教育",  "娱乐", "体育", "时尚", "科技"]:
        choice.append(config[i])

    #choice 选择列表，与下列表对应，1选中，0未选中
    part_list1 = ["edu", "ent", "sports", "fashion", "tech"] # 待选择板块
    chooselist = []
    j = 0
    for i in part_list1:
        if choice[j] == 1:
            chooselist.append(i)
        j=j+1
    # print(chooselist)
    resultdic={}

    for part in chooselist:

        resultdic[translation(part)] = []
        url = "http://"+part+".sina.com.cn/"
        response = requests.get(url,headers=headers).content.decode("utf-8","ignore")
        html = etree.HTML(response)

        if part =="sports":
            style = 'display:none!important;'
        else:
            style = 'display:none!important;height:0!important;overflow:hidden!important;'

        title_result = html.xpath('//div[@style="'+style+'"]/ul/li/a')
        url_result = html.xpath('//div[@style="'+style+'"]/ul/li/a/@href')
        if len(title_result) <=20:
            num_to_get = len(title_result)
        else:
            num_to_get = 20
        for i in range(num_to_get):
            temp=[]
            temp.append(title_result[i].text)
            temp.append(date_form_XL(url_result[i]))
            temp.append(absrtact_XL(url_result[i]))
            temp.append(url_result[i])
            resultdic[translation(part)].append(temp)
    NewsDic['新浪'] = resultdic
    return
    
def write_News(NewsDic, filename):
    with open(filename+".json",'w',encoding='utf-8') as f:
        json.dump(NewsDic,f, ensure_ascii=False)
        
def get_argc():
    if len(sys.argv) == 1:
        return 1
    else:
        return str((sys.argv)[1])

def date_aquire():
    time.localtime(time.time())
    return str(time.strftime(r'%Y-%m-%d',time.localtime(time.time())))

def pre_aquire():
    with open("教务处.json",'rb') as f:
        pre_data=json.load(f)
    return pre_data["教务处"]["通知公告"]

def page_1(url, headers, resultlist):
    response = requests.get(url,headers=headers).content
    html = etree.HTML(response)

    _title_result = html.xpath('//li/div[@class="crules_con"]/a')
    title_result = []
    for i in range(len(_title_result)):
        title_result.append(re.sub(r'[\s]' ,'',_title_result[i].text))
    
    _url_result = html.xpath('//li/div[@class="crules_con"]/a/@href')
    url_result = []
    for i in range(len(_url_result)):
        url_result.append('http://jwc.bit.edu.cn/tzgg/'+_url_result[i])

    date_result = html.xpath('//li/div[@class="crules_con"]/span')
    
    date_now = date_aquire()
    for i in range(len(title_result)):
        if date_result[i].text[0] == '0':
                month = date_result[i].text[1]
        else:
            month = date_result[i].text[0:2]

        if date_now[5] == '0':
            month_now = date_now[6]
        else:
            month_now = date_now[5:7]
                
        if eval(month) == eval(month_now):
            temp = []
            temp.append(title_result[i])
            temp.append('')
            temp.append(date_result[i].text)
            temp.append(url_result[i])
            resultlist.append(temp)
        else:
            pass

def func_info(headers):
    result = []
    
    url = "http://jwc.bit.edu.cn/tzgg/index.htm"
    page_1(url,headers,result)
    url = "http://jwc.bit.edu.cn/tzgg/index1.htm"
    page_1(url,headers,result)
    
    pre_info = pre_aquire()
    new_info = []
    if pre_info == []:
        new_info = result
    else:
        
        for i in range(len(result)):
            flag = 0
            for j in range(len(pre_info)):
                if result[i][0] == pre_info[j][0]:
                    flag = 1
                else:
                    pass
            if flag == 0:
                new_info.append(result[i])

    with open("notes.json",'w',encoding='utf-8') as f:
        json.dump(new_info,f, ensure_ascii=False)

    return result

def page_2(url, headers, resultlist, part):
    url1 = 'http://jwc.bit.edu.cn/'+part+'/index.htm'
    _response = requests.get(url1,headers=headers).content
    html = etree.HTML(_response)
    _url_result_1 = html.xpath('//aside[@class="sub_navm"]/ul/li/a/@href')
    for i in range(len(_url_result_1)):
        url2 = 'http://jwc.bit.edu.cn/'+part+'/'+_url_result_1[i]
        response = requests.get(url2,headers=headers).content
        html = etree.HTML(response)

        _title_result = html.xpath('//li/div[@class="crules_con"]/a')
        title_result = []
        for i in range(len(_title_result)):
            title_result.append(re.sub(r'[\s]' ,'',_title_result[i].text))

        _url_result = html.xpath('//li/div[@class="crules_con"]/a/@href')
        url_result = []
        for i in range(len(_url_result)):
            url_result.append(re.sub('index.htm','',url2)+_url_result[i])

        date_result = html.xpath('//li/div[@class="crules_con"]/span')

        date_now = date_aquire()
        
        for i in range(len(title_result)):
            
            if date_result[i].text[0] == '0':
                month = date_result[i].text[1]
            else:
                month = date_result[i].text[0:2]

            if date_now[5] == '0':
                month_now = date_now[6]
            else:
                month_now = date_now[5:7]
            
            if eval(month) == eval(month_now):
                temp = []
                temp.append(title_result[i])
                temp.append('')
                temp.append(date_result[i].text)
                temp.append(url_result[i])
                resultlist.append(temp)
            else:
                pass

def JWCspider(headers, NewsDic, data):
    data = setting_aquire()
    
    choice=[]
    config = data["教务处"]
    for i in ["国际教育", "实践教学", "教务学籍"]:
        choice.append(config[i])

    #choice 选择列表，与下列表对应，1选中，0未选中edu tech
    part_list1 = ["gjjl", "sjjx", "jwyx"] # 待选择板块
    chooselist = []
    j = 0
    for i in part_list1:
        if choice[j] == 1:
            chooselist.append(i)
        j=j+1
    # print(chooselist)
    resultdic={}
    resultdic[translation('tzgg')] = func_info(headers)#通知公告
    NewsDic["教务处"] = resultdic
    for part in chooselist:
        resultdic[translation(part)] = [] 
        url = 'http://jwc.bit.edu.cn/'+part+'/index.htm'
        page_2(url,headers,resultdic[translation(part)], part)
        url = 'http://jwc.bit.edu.cn/'+part+'/index1.htm'
        page_2(url,headers,resultdic[translation(part)], part)

if __name__ == "__main__":
    headers={
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleW\
    ebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36"
    }
    NewsDic = {}
    data = setting_aquire()
    # website_chose = get_argc()
    website_chose = '人民网'
    filename = ''
    if website_chose == '人民网':
        RMspider(headers, NewsDic, data)
        filename = '人民网'
    elif website_chose == '网易':
        WYspider(headers, NewsDic, data)
        filename = '网易'
    elif website_chose == '新浪':
        XLspider(headers, NewsDic, data)
        filename = '新浪'
    elif website_chose == '教务处':
        JWCspider(headers, NewsDic, data)
        filename = '教务处'
    else:
        print("**FATAL ERROR**!\nWrong parameter input!")

    if filename != '':  
        write_News(NewsDic, filename)
    print('done')
#---------------------------
# 作者：韩静远
# 2019-12-6
# 北京理工大学
# qq：656239490
