#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

char Lower_case(char ch)		// To convert alphabet as lower case.
{
	if ('A' <= ch && ch <= 'Z')	// [character가 Upper case일 경우, Lower case 의 ascii code를 return.]
		return ch - 'A' + 'a';
	else									// [character가 Lower case일 경우, 그대로 return.]
		return ch;
}

int solution(string word, vector<string> pages)
{
	for (int i = 0; i < word.size(); i++)			// To convert alphabet as lower case.
		word[i] = Lower_case(word[i]);		// [Search를 할 단어인 word를 lower case로 변환.]

	int N = pages.size();							// N = The size of total page data.
	unordered_map<string, int> link_idx;		// link_idx = The table of link and index altogether. [Link와 index를 저장하고 있는 table.]
	vector<pair<int, vector<string>>> web(N, { 0, vector<string>() }); // The table of base score and external link. [기본 점수와 외부 링크를 저장하고 있는 table.]

	for (int i = 0; i < N; i++)			// Search through all pages individually.
	{											// [Page의 정보를 차례대로 search.]
		string html = pages[i];			// html = The memory of total html data. [html의 전체 data를 저장.]

		// [<head> 내부의 <meta> data 내부에 저장된 http link의 주소를 추출하는 과정.]
		string https = "";					// https = The temporary memory to figure out address of http. [http의 주소를 저장하기 위한 임시 메모리.]
		int start_meta = 0;				// start_meta = The temporary index memory to store the start point of finding certain word.
												// [특정 word에 대한 find의 이후 시작 index를 저장하고 있기 위함,]
		while (https == "")
		{
			start_meta = html.find("<meta") + 5;						// [<head>내부에 <meta>가 여러개 존재할 수 있기 때문에, 차례대로 <meta>~</meta>를 search하기 위함.]
			int end_meta = html.substr(start_meta).find(">");	// [start_meta는 <meta>내부 data의 시작 point, end_meta는 </meta>의 end point를 저장.]
			html = html.substr(start_meta);								// [html은 <meta>~</meta>를 차례대로 sub string 하면서 search하게 된다.]
			start_meta = html.find("https://");							// [현재 search하는 <meta>~</html> 내부에 존재하는 http link의 point를 저장.]

			if (end_meta < start_meta)		// [end_meta < start_meta 라는 것은, find한 http link의 위치가 현재 search 중인 <meta>~</meta>가 아닌 
				continue;							// 외부 <meta>~</meta>내부에 존재한다는 것을 의미한다.]

			while (html[start_meta] != '\"')		// [제대로된 http link의 위치를 찾은 경우, \n 전까지 완전한 http link를 extract.]	
				https += html[start_meta++];		// [find한 http의 시작 위치, start_meta 부터 \n까지 character로 저장.]

			link_idx[https] = i;					// [link와 index를 저장하고 있는 table에 extract한 https link의 주소와 index를 저장.]
		}

		// [<body> 내부의 text data를 extract 하여, word의 matching score를 count하기 위한 과정.]
		int start_body = html.find("<body>") + 6;	// [start_body는 <body> 내부의 text data의 시작 point를 저장.]
		int end_body = html.find("</body>");			// [end_body는 </body>의 end point를 저장.]
		
		// [Text data를 character 단위로 search하면서, 조건에 맞는 경우 차례대로 저장하면서 word와 matching 되는 것을 count 하는 과정.]
		string temp = "";					// temp = The temporary memory of making word. [Character를 한 개씩 비교하면서, 조건에 맞는경우 word로 만들기 위함.]
		bool bracket = false;			// bracket = The flag memory of bracket. [<> 괄호 내부를 search 중인지 판단하기 위한 flag memory.]
		for (int k = start_body; k < end_body; k++)
		{
			char cur_char = Lower_case(html[k]);		// cur_char = The current character. [Character 한 개씩 확인하기 위한 memory.]

			if (bracket)						// [ '<>' 내부는 search할 필요가 없기 때문에 빠르게 search 하기 위해 구분 지은 것.]		
			{
				if (cur_char == '>')		// [현재 character가 '<' 의 내부를 search 하다가 '>'를 마주한 경우, 
					bracket = false;		// '<>' 를 벗어났기 때문에, 다시 false로 초기화.]
			}

			else if (cur_char == ' ' || !('a' <= cur_char && cur_char <= 'z'))		// [현재 character가 a~z 문자가 아니고, ' ' 공백도 아닌 경우.]
			{
				if (temp != "" && temp == word)	// [숫자 or 특수 문자 등이 나왔을 경우, word와 temp가 동일한지 판단한다.]
					web[i].first++;						// [word와 temp가 same일 경우, base score(기본점수) 증가.]

				temp = "";									// [' '공백 or 숫자 or 특수 문자 등 word와 비교할 기점이 되었으니, 비교 후 ""로 초기화.]

				if (cur_char == '<')		// [현재 character가 '<'의 내부를 search 시작한 경우,
					bracket = true;		// bracket의 내부를 search할 필요가 없기 때문에 true로 변경.]
			}

			else								// [a~z의 문자인 경우, word와 matching 되는지 판단하기 위해 character를 순차적으로 저장.]
				temp += cur_char;
		}

		if (temp != "" && temp == word)		// [Loop의 마지막 search 이후, 만들어진 최종의 temp와 word가 matching 되는지 비교.]
			web[i].first++; 

		// [<body>~</body> 내부에 존재하는 <a>~</a>의 외부 link 정보를 extract 하고, 리으크 점수를 count하는 과정.]
		html = html.substr(start_body);
		int start_link = html.find("<a href");	// [start_link는 <body> 내부의 <a>내부 data의 시작 point를 저장.]

		while (start_link != string::npos)			// [string::npos는 string::find()로 찾은 값이 없을 경우, return되는 값이다.]
		{													// [즉, npos가 return 되었다는 것은 <body>~</body> 내부에 <a>~</a>가 존재하지 않는 경우를 말한다.]
			html = html.substr(start_link + 7);
			html = html.substr(html.find("https://"));	// [<body> 내부에서 외부 link의 정보 <a>~</a>에 저장된 https link의 정보를 find.]
			web[i].second.push_back(html.substr(0, html.find("\"")));	// [각 page의 base score(기본점수)와 외부 링크의 정보를 저장하는 web table에 external link 주소를 저장.]
			start_link = html.find("<a href");	// [<a>~</a>가 여러개 존재할 수 있기 때문에, 다음 <a>~</a>가 존재하는지 find.]	
		}
	}

	// [각 page의 matching score를 계산하기 위해, base score와 link score를 계산하는 과정.]
	vector<double> match_score(N, 0);		// match_score = The memory of storing total match score.
	for (int i = 0; i<N; i++)
	{														// [web.first = base score.		web.second = external link's address.]
		match_score[i] += web[i].first;			// [web table을 참조하여, page의 base score를 저장.]

		double link_score = 0;						// link_score = The result of dividing base score and the number of external link.			
		if (web[i].second.size() != 0)			// [divided by zero의 Exception을 방지하기 위한 condition.]
			link_score = (double)web[i].first / (double)web[i].second.size();	// [Link score = base score / the number of external link.]

		for (int j = 0; j < web[i].second.size(); j++)		// [현재 page에서 연결되어 있는 external link의 수 만큼, 각 각 연산해주기 위한 loop.]
		{																// [link_idx는 link와 index를 key-value로 저장하고 있는 map memory.]				
			if (link_idx.find(web[i].second[j]) != link_idx.end())		// [map.find()로 찾는 값이 없는 경우, map.end()를 return해준다.]
			{															// [즉, map.end()라는 것은 현재 page에서 연결된 external link 의 주소가 모든 link의 정보를 저장하고 있는 table에 존재하지 않는 것을 의미한다.]
				int idx = link_idx[web[i].second[j]];		// idx = The index of current page which was searched in table. [link의 index를 저장.]
				match_score[idx] += link_score;			// [find()한 index를 참조하여 link score를 match socre 메모리에 연산해준다.]
			}
		}
	}
	
	// [The highest match score를 가진 link의 index를 extract하기 위한 과정.]
	int answer = 0;
	for (int i = 0; i < N; i++)
		if (match_score[answer] < match_score[i])	// [match score의 table을 0~N까지 search하면서, highest match score를 가진 link의 index를 저장.]
			answer = i;

	return answer;		// Index return.
}

int main(void)
{
	ios_base::sync_with_stdio(false);

	//string word = "Blind";
	//vector<string> pages = { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>" };
	string word = "Muzi";
	vector<string> pages = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"};
	cout << solution(word, pages) << endl;
}