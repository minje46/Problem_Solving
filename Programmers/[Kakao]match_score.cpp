#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

char Lower_case(char ch)		// To convert alphabet as lower case.
{
	if ('A' <= ch && ch <= 'Z')	// [character�� Upper case�� ���, Lower case �� ascii code�� return.]
		return ch - 'A' + 'a';
	else									// [character�� Lower case�� ���, �״�� return.]
		return ch;
}

int solution(string word, vector<string> pages)
{
	for (int i = 0; i < word.size(); i++)			// To convert alphabet as lower case.
		word[i] = Lower_case(word[i]);		// [Search�� �� �ܾ��� word�� lower case�� ��ȯ.]

	int N = pages.size();							// N = The size of total page data.
	unordered_map<string, int> link_idx;		// link_idx = The table of link and index altogether. [Link�� index�� �����ϰ� �ִ� table.]
	vector<pair<int, vector<string>>> web(N, { 0, vector<string>() }); // The table of base score and external link. [�⺻ ������ �ܺ� ��ũ�� �����ϰ� �ִ� table.]

	for (int i = 0; i < N; i++)			// Search through all pages individually.
	{											// [Page�� ������ ���ʴ�� search.]
		string html = pages[i];			// html = The memory of total html data. [html�� ��ü data�� ����.]

		// [<head> ������ <meta> data ���ο� ����� http link�� �ּҸ� �����ϴ� ����.]
		string https = "";					// https = The temporary memory to figure out address of http. [http�� �ּҸ� �����ϱ� ���� �ӽ� �޸�.]
		int start_meta = 0;				// start_meta = The temporary index memory to store the start point of finding certain word.
												// [Ư�� word�� ���� find�� ���� ���� index�� �����ϰ� �ֱ� ����,]
		while (https == "")
		{
			start_meta = html.find("<meta") + 5;						// [<head>���ο� <meta>�� ������ ������ �� �ֱ� ������, ���ʴ�� <meta>~</meta>�� search�ϱ� ����.]
			int end_meta = html.substr(start_meta).find(">");	// [start_meta�� <meta>���� data�� ���� point, end_meta�� </meta>�� end point�� ����.]
			html = html.substr(start_meta);								// [html�� <meta>~</meta>�� ���ʴ�� sub string �ϸ鼭 search�ϰ� �ȴ�.]
			start_meta = html.find("https://");							// [���� search�ϴ� <meta>~</html> ���ο� �����ϴ� http link�� point�� ����.]

			if (end_meta < start_meta)		// [end_meta < start_meta ��� ����, find�� http link�� ��ġ�� ���� search ���� <meta>~</meta>�� �ƴ� 
				continue;							// �ܺ� <meta>~</meta>���ο� �����Ѵٴ� ���� �ǹ��Ѵ�.]

			while (html[start_meta] != '\"')		// [����ε� http link�� ��ġ�� ã�� ���, \n ������ ������ http link�� extract.]	
				https += html[start_meta++];		// [find�� http�� ���� ��ġ, start_meta ���� \n���� character�� ����.]

			link_idx[https] = i;					// [link�� index�� �����ϰ� �ִ� table�� extract�� https link�� �ּҿ� index�� ����.]
		}

		// [<body> ������ text data�� extract �Ͽ�, word�� matching score�� count�ϱ� ���� ����.]
		int start_body = html.find("<body>") + 6;	// [start_body�� <body> ������ text data�� ���� point�� ����.]
		int end_body = html.find("</body>");			// [end_body�� </body>�� end point�� ����.]
		
		// [Text data�� character ������ search�ϸ鼭, ���ǿ� �´� ��� ���ʴ�� �����ϸ鼭 word�� matching �Ǵ� ���� count �ϴ� ����.]
		string temp = "";					// temp = The temporary memory of making word. [Character�� �� ���� ���ϸ鼭, ���ǿ� �´°�� word�� ����� ����.]
		bool bracket = false;			// bracket = The flag memory of bracket. [<> ��ȣ ���θ� search ������ �Ǵ��ϱ� ���� flag memory.]
		for (int k = start_body; k < end_body; k++)
		{
			char cur_char = Lower_case(html[k]);		// cur_char = The current character. [Character �� ���� Ȯ���ϱ� ���� memory.]

			if (bracket)						// [ '<>' ���δ� search�� �ʿ䰡 ���� ������ ������ search �ϱ� ���� ���� ���� ��.]		
			{
				if (cur_char == '>')		// [���� character�� '<' �� ���θ� search �ϴٰ� '>'�� ������ ���, 
					bracket = false;		// '<>' �� ����� ������, �ٽ� false�� �ʱ�ȭ.]
			}

			else if (cur_char == ' ' || !('a' <= cur_char && cur_char <= 'z'))		// [���� character�� a~z ���ڰ� �ƴϰ�, ' ' ���鵵 �ƴ� ���.]
			{
				if (temp != "" && temp == word)	// [���� or Ư�� ���� ���� ������ ���, word�� temp�� �������� �Ǵ��Ѵ�.]
					web[i].first++;						// [word�� temp�� same�� ���, base score(�⺻����) ����.]

				temp = "";									// [' '���� or ���� or Ư�� ���� �� word�� ���� ������ �Ǿ�����, �� �� ""�� �ʱ�ȭ.]

				if (cur_char == '<')		// [���� character�� '<'�� ���θ� search ������ ���,
					bracket = true;		// bracket�� ���θ� search�� �ʿ䰡 ���� ������ true�� ����.]
			}

			else								// [a~z�� ������ ���, word�� matching �Ǵ��� �Ǵ��ϱ� ���� character�� ���������� ����.]
				temp += cur_char;
		}

		if (temp != "" && temp == word)		// [Loop�� ������ search ����, ������� ������ temp�� word�� matching �Ǵ��� ��.]
			web[i].first++; 

		// [<body>~</body> ���ο� �����ϴ� <a>~</a>�� �ܺ� link ������ extract �ϰ�, ����ũ ������ count�ϴ� ����.]
		html = html.substr(start_body);
		int start_link = html.find("<a href");	// [start_link�� <body> ������ <a>���� data�� ���� point�� ����.]

		while (start_link != string::npos)			// [string::npos�� string::find()�� ã�� ���� ���� ���, return�Ǵ� ���̴�.]
		{													// [��, npos�� return �Ǿ��ٴ� ���� <body>~</body> ���ο� <a>~</a>�� �������� �ʴ� ��츦 ���Ѵ�.]
			html = html.substr(start_link + 7);
			html = html.substr(html.find("https://"));	// [<body> ���ο��� �ܺ� link�� ���� <a>~</a>�� ����� https link�� ������ find.]
			web[i].second.push_back(html.substr(0, html.find("\"")));	// [�� page�� base score(�⺻����)�� �ܺ� ��ũ�� ������ �����ϴ� web table�� external link �ּҸ� ����.]
			start_link = html.find("<a href");	// [<a>~</a>�� ������ ������ �� �ֱ� ������, ���� <a>~</a>�� �����ϴ��� find.]	
		}
	}

	// [�� page�� matching score�� ����ϱ� ����, base score�� link score�� ����ϴ� ����.]
	vector<double> match_score(N, 0);		// match_score = The memory of storing total match score.
	for (int i = 0; i<N; i++)
	{														// [web.first = base score.		web.second = external link's address.]
		match_score[i] += web[i].first;			// [web table�� �����Ͽ�, page�� base score�� ����.]

		double link_score = 0;						// link_score = The result of dividing base score and the number of external link.			
		if (web[i].second.size() != 0)			// [divided by zero�� Exception�� �����ϱ� ���� condition.]
			link_score = (double)web[i].first / (double)web[i].second.size();	// [Link score = base score / the number of external link.]

		for (int j = 0; j < web[i].second.size(); j++)		// [���� page���� ����Ǿ� �ִ� external link�� �� ��ŭ, �� �� �������ֱ� ���� loop.]
		{																// [link_idx�� link�� index�� key-value�� �����ϰ� �ִ� map memory.]				
			if (link_idx.find(web[i].second[j]) != link_idx.end())		// [map.find()�� ã�� ���� ���� ���, map.end()�� return���ش�.]
			{															// [��, map.end()��� ���� ���� page���� ����� external link �� �ּҰ� ��� link�� ������ �����ϰ� �ִ� table�� �������� �ʴ� ���� �ǹ��Ѵ�.]
				int idx = link_idx[web[i].second[j]];		// idx = The index of current page which was searched in table. [link�� index�� ����.]
				match_score[idx] += link_score;			// [find()�� index�� �����Ͽ� link score�� match socre �޸𸮿� �������ش�.]
			}
		}
	}
	
	// [The highest match score�� ���� link�� index�� extract�ϱ� ���� ����.]
	int answer = 0;
	for (int i = 0; i < N; i++)
		if (match_score[answer] < match_score[i])	// [match score�� table�� 0~N���� search�ϸ鼭, highest match score�� ���� link�� index�� ����.]
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