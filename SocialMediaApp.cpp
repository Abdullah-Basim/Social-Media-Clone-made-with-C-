#include<fstream>
#include <iostream>
using namespace std;

class Post;
class Comment;
class Date;
class Facebook;
class user;
class page;


class Helper
{
public:
	static int Stringlength(char* arr)
	{
		int i = 0;
		while (arr[i] != '\0')
			i++;

		return i;
	}

	static char* DeepCopy(char* arr1, char* arr2)
	{
		int size = Stringlength(arr2);
		arr1 = new char[size + 1];
		for (int i = 0; i < size; i++)
		{
			arr1[i] = arr2[i];
		}
		arr1[size] = '\0';
		return arr1;
	}

	static char* GetStringFromBuffer(char* temp)
	{
		int size = Stringlength(temp);
		char* arr = 0;
		arr = DeepCopy(arr, temp);
		return arr;
	}

	static bool CompareStrings(char* arr1, char* arr2)
	{
		int size1 = Stringlength(arr1);
		int size2 = Stringlength(arr2);

		if (size1 == size2)
		{
			for (int i = 0; i < size1; i++)
			{
				if (arr1[i] == arr2[i])
					;
				else
					return false;
			}

			return true;


		}
		else
			return false;
	}
};

class object
{
	char* id;

public:

	object()
	{
		id = 0;
	}

	virtual ~object()
	{
		if (id != 0)
			delete id;
	}

	void AddIdforShare(char* arr)
	{
		id = Helper::GetStringFromBuffer(arr);
	}

	void AddidforLike(char* arr)
	{
		id = Helper::GetStringFromBuffer(arr);
	}

	void setID(char* str)
	{
		id = Helper::DeepCopy(id, str);
	}

	virtual char* getID()
	{
		return id;
	}

};

class Date
{
	int day, month, year;
public:

	Date()
	{
		day = 0; month = 0; year = 0;
	}

	static Date CurrentDate;

	void SetDate(istream& fin)
	{
		int tdate;
		fin >> tdate;
		day = tdate;
		fin >> tdate;
		month = tdate;
		fin >> tdate;
		year = tdate;
	}

	void SetDate(int tday, int tmonth, int tyear)
	{
		CurrentDate.day = tday;
		CurrentDate.month = tmonth;
		CurrentDate.year = tyear;

	}

	int getday()
	{
		return day;
	}

	int getmonth()
	{
		return month;
	}

	int getyear()
	{
		return year;
	}

	void PrintDate()
	{
		cout << "(" << day << "/" << month << "/" << year << ")";
	}

};

Date Date::CurrentDate;



class Activity
{
	int type;
	char* value;
public:

	Activity()
	{
		type = 0;
		value = 0;
	}

	~Activity()
	{
		if (value != 0)
		{
			delete value;
		}

	}

	void LoadActivity(ifstream& fin)
	{
		fin >> type;
		fin.ignore();
		char temp[80];
		fin.getline(temp, 80);
		value = Helper::GetStringFromBuffer(temp);
	}

	void PrintActivity()
	{
		if (type == 1)
		{
			cout << " is feeling ";
			int size = Helper::Stringlength(value);
			for (int i = 0; i < size; i++)
			{
				cout << value[i];
			}
		}
		else if (type == 2)
		{
			cout << " is thinking about ";
			int size = Helper::Stringlength(value);
			for (int i = 0; i < size; i++)
			{
				cout << value[i];
			}
		}
		else if (type == 3)
		{
			cout << " is making ";
			int size = Helper::Stringlength(value);
			for (int i = 0; i < size; i++)
			{
				cout << value[i];
			}
		}
		else if (type == 4)
		{
			cout << " is celebrating ";
			int size = Helper::Stringlength(value);
			for (int i = 0; i < size; i++)
			{
				cout << value[i];
			}
		}
	}
};

class Comment
{
	char* ID;
	char* postid;
	char* text;
	object* userwhocommented;

public:

	Comment()
	{
		ID = 0;
		postid = 0;
		text = 0;
		userwhocommented = 0;
	}

	~Comment()
	{
		if (ID != 0)
			delete[] ID;

		if (postid != 0)
			delete[] postid;

		if (text != 0)
			delete[] text;

		if (userwhocommented != 0)
			delete userwhocommented;

	}

	Comment* Makeanewcomment(int totalnoofcomments,char* postidofcom,char* textofcomment,object* userofcom)
	{
		Comment* c=new Comment;
		c->ID = new char[3];
		c->ID[0] = 'c';
		c->ID[1] = totalnoofcomments + 1;
		c->ID[2] = '\0';

		c->postid = postidofcom;
		c->text = textofcomment;
		c->userwhocommented = userofcom; 
		return c;
	}

	void ReadDatafromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		fin.ignore();
		ID = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		fin.ignore();
		postid = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		fin.ignore();
		char* arr = Helper::GetStringFromBuffer(temp);
		userwhocommented = new object;
		userwhocommented->setID(arr);
		fin.getline(temp, 80);
		text = Helper::GetStringFromBuffer(temp);
	}

	void setCommentator(char* id)
	{
		ID = id;
	}

	object* getCommentator()
	{
		return userwhocommented;
	}

	char* getpostid()
	{
		if (postid != 0)
			return postid;
		else
			return 0;
	}

	void PrintID()
	{
		cout << ID;
	}

	void PrintComment(user** fbusers, page** fbpages, int totalfbusers, int totalfbpages);
	/*{
		object* obj = userwhocommented;
		char* id = obj->getID();
		Facebook fb;
		if (id[0] == 'u')
		{
			user* u;
			u = fb.SearchUserByIndex(id);
			u->PrintName();
		}
		else
		{
			page* p;
			p = fb.SearchPageByIndex(id);
			p->PrintName();
		}
		cout << " wrote ";
		int size = Helper::Stringlength(text);
		for (int i = 0; i < size; i++)
			cout << text[i];
	}*/

	void PrintCommentofpost(char* arr)
	{
		//cout << userwhocommented->id;
		if (Helper::CompareStrings(arr, postid))
		cout << " wrote ";
		int size = Helper::Stringlength(text);
		for (int i = 0; i < size; i++)
			cout << text[i];
	}

};


class Post : public object
{
	Activity* act;
	char* postid;
	char* text;
	Date shared_date;
	object* sharedby;
	object** likedby;
	Comment** comments;
	int commentcount;
	int likecount;
	int sharecount;
public:
	Post() :shared_date()
	{
		act = 0;
		sharedby = 0;
		likedby = 0;
		comments = new Comment* [10];
		for (int i = 0; i < 10; i++)
		{
			comments[i] = 0;
		}
		postid = 0;
		text = 0;
		commentcount = 0;
		likecount = 0;
		sharecount = 0;
	}

	~Post()
	{
		if (act != 0)
			delete act;

		if (postid != 0)
			delete postid;

		if (text != 0)
			delete text;

		if (sharedby != 0)
			delete sharedby;

		if (likedby != 0)
		{
			for (int i = 0;i < likecount;i++)
				delete likedby[i];

			//delete[] likedby;
		}

		for (int i = 0; comments[i]!= 0 ; i++)
			delete comments[i];

		delete[] comments;
	}

	void ReadDatafromFile(ifstream& fin)
	{
		int posttype = 0;
		fin >> posttype;
		if (posttype == 1)
		{
			char temp[80];
			fin >> temp;
			postid = Helper::GetStringFromBuffer(temp);
			shared_date.SetDate(fin);
			fin.ignore();
			fin.getline(temp, 80);
			text = Helper::GetStringFromBuffer(temp);
			act = 0;
		}
		else if (posttype == 2)
		{
			char temp[80];
			fin >> temp;
			postid = Helper::GetStringFromBuffer(temp);
			shared_date.SetDate(fin);
			fin.ignore();
			fin.getline(temp, 80);
			text = Helper::GetStringFromBuffer(temp);
			act = new Activity;
			act->LoadActivity(fin);
		}
		else
			cout << "Post type is undefined";

	}

	void SharePost(char* id)
	{
		sharedby = new object;
		sharedby->AddIdforShare(id);
	}

	void setSharedby(object* user)
	{
		if (sharecount < 10)
		{
			sharedby = user;
		}
		else
		{
			cout << "MAXIMUM USERS HAVE SHARED\n";
		}
	}

	void ViewPost(user** fbusers, page** fbpages, int totalfbusers, int totalfbpages);

	void veiwLikedBy(user** fbusers, page** fbpages, int totalfbusers, int totalfbposts);

	void Addcomment(Comment* c, int ctr)
	{
		this->comments[ctr] = c;
	}

	void Addnewcomment(user* cuser, char* text, int totalnoofcomments);

	void AllocateLikedbyLst(int usersliked)
	{
		likedby = new object * [usersliked];
		likecount = usersliked;
		for (int i = 0; i < usersliked; i++)
		{
			likedby[i] = new object;
		}

	}

	void LikePost(char* arr, int ctr)
	{
		likedby[ctr]->AddidforLike(arr);
	}

	void Addnullonlikepost()
	{
		likedby = new object * [0];
		likedby[0] = nullptr;
	}

	void setDescription(char* des)
	{
		Helper::DeepCopy(text, des);
	}

	void PrintDetailedView()
	{
		this->act->PrintActivity();
		cout << endl;
		cout << text << "\t\t";;
		this->shared_date.PrintDate();
	}


	char* getDescription()
	{
		return text;
	}

	void setDate(Date date)
	{
		shared_date = date;
	}
	Date getDate()
	{
		return shared_date;
	}
	Comment** getComment()
	{
		return comments;
	}
	int getCommentCount()
	{
		return commentcount;
	}
	int postedDay()
	{
		return shared_date.getday();
	}

	void setCommentCount(int a)
	{
		commentcount = a;
	}
	object* getSharedby()
	{
		return sharedby;
	}
	int getSharedCount()
	{
		return sharecount;
	}

	int getLikecount()
	{
		return likecount;
	}
	void setLikeCount(int _count)
	{
		likecount = _count;
	}

	
	void Settext(char* id)
	{
		text = Helper::DeepCopy(text, id);
	}

	char* Gettext()
	{
		return this->text;
	}

	void setLikedUser(object** _liked)
	{
		if (likedby == NULL)
		{
			likedby = new object * [10];
			for (int i = 0; i < 10; i++)
				likedby[i] = 0;
		}
		for (int i = 0; i < likecount; i++)
		{
			likedby[i] = _liked[i];
		}
	}

	object** getLiked()
	{
		return likedby;
	}

	char* GETID()
	{
		return postid;
	}

	void  LikePost(char a[5])
	{
		char* temp[10] = { 0 };
		int i = 0;
		for (; i < likecount; i++)
		{
			//temp[i] = Helplikedby[i]->id;
			temp[i] = Helper::DeepCopy(temp[i], likedby[i]->getID());
		}

		for (int j = 0; j < likecount; j++)
		{
			if (likedby[j] != NULL)
				delete likedby[j];
		}

		int length = likecount + 1;

		likedby = new object * [length];
		int k = 0;
		for (; k < length; k++)
		{
			likedby[k] = new object;
			if (k != length - 1)
				likedby[k]->setID(temp[k]) ;
			if (k == length - 1)
			{
				//char a[5] = "u7";                                       //the new liker is the current user
				likecount++;
				likedby[k]->setID(a);
			}
		}
	}



};

class Memory : public Post
{
private:
	Post* Mem;
public:
	Memory()
	{
		Mem = 0;
	}

	~Memory()
	{
		if (Mem != 0)
		{
		  Mem = 0;
		  this->setSharedby(0);
		}
	}

	void SetMemory(Post* p)
	{
		//		Mem = new Post;
		Mem = p;
	}

	Post* GetPost()
	{
		return Mem;
	}

	void ShareMemory(Post* p,char* text,object* obj)
	{
		Mem = p;
		this->Settext(text);
		this->setDate(p->getDate());
		this->setSharedby(obj);
	}

	void PrintMemory(user* cuser, Memory* mem);
};

class page
{
	char* id;
	char* title;
	Post** timeline;
	int noofposts = 0;
public:
	page()
	{
		id = 0;
		title = 0;
		timeline = 0;
	}

	~page()
	{
		if (id != 0)
			delete id;
		if (title != 0)
			delete title;
		if (timeline != 0)
		{
			for (int i = 0; i < noofposts; i++)
				delete timeline[i];

			delete[] timeline;
		}

	}
	void Readpagefromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		this->id = Helper::GetStringFromBuffer(temp);
		fin.ignore();
		fin.getline(temp, 80);
		this->title = Helper::GetStringFromBuffer(temp);
	}

	int returnid()
	{
		int m = id[1] - 48;
		if (id[2] != '\0')
			m = m * 10 + id[2] - 48;

		return m;
	}

	page* SearchPageByIndex(char* arr1,page** fbpages,int totalfbpages)
	{
		int m = arr1[1] - 48;
		if (arr1[2] != '\0')
		{
			int m2 = arr1[2] - 48;
			m = m * 10 + m2;
		}
		for (int i = 0; i < totalfbpages; i++)
		{
			int n = fbpages[i]->returnid();
			if (m == n)
			{
				return fbpages[i];
			}
		}
		return 0;
	}

	char* getidofpage()
	{
		return id;
	}

	

	void PrintPage()
	{
		/*if (this != 0)
			;*/

		int size = Helper::Stringlength(this->id);
		for (int i = 0; i < size; i++)
		{
			cout << id[i];
		}
		cout << "\t";
		size = Helper::Stringlength(this->title);
		for (int i = 0; i < size; i++)
		{
			cout << title[i];
		}

		cout << endl;

	}

	void printdetailedveiw(user** fbusers, page** fbpages, int totalfbusers, int totalfbpages)
	{
			for (int i = 0; i < noofposts; i++)
			{
				timeline[i]->ViewPost(fbusers, fbpages, totalfbusers, totalfbpages);
			}

			cout << endl;

		
	}

	void PrintName()
	{
		int size = Helper::Stringlength(this->title);
		for (int i = 0; i < size; i++)
		{
			cout << title[i];
		}
	}

	void Printdetailedview()
	{
		;
	}

	void InitializeTimeline(int posts)
	{
		if (posts > 0)
		{
			noofposts = posts;
			if (timeline == 0)
			{
				timeline = new Post * [posts];
			}
		}
		else
			timeline = 0;
	}

	void AddTimeline(Post* p, int ctr)
	{
		if (timeline != nullptr)
		{
			timeline[ctr] = p;
		}
	}


};

class user : public object
{
private:
	char* id;
	char* fsname;
	char* lsname;
	user** freindlist;
	page** likedpages;
	Post** timeline;
	int nooffriends = 0;
	int nooflikedpages = 0;
	int noofposts = 0;
	Memory* memory;

public:
	user()
	{
		memory = 0;
		id = 0;
		fsname = 0;
		lsname = 0;
		freindlist = 0;
		likedpages = 0;
		//timeline = new Post * [1];
		timeline = 0;
	}

	~user()
	{
		if (id != 0)
			delete[] id;
		if (fsname != 0)
			delete[] fsname;
		if (lsname != 0)
			delete[] lsname;
		if (freindlist != 0)
		{
			delete[] freindlist;  //it will delete all users entered but didnt delete the users pointers present in the list otherwise those users will be dangling
		}
		if (likedpages != 0)
		{

			delete[] likedpages; //Similar for liked pages it will just delete liked pages stored inthis it will not delete actual pages pointers
		}

		if (timeline != 0)
		{
			for (int i = 0; i < noofposts; i++)
				delete timeline[i];

			delete[] timeline;
		}
		if (memory != 0)
			delete memory;
	}

	user** Getfreinds()
	{
		return freindlist;
	}

	Memory* GetMemory()
	{
		return memory;
	}



	Post* GetPost(int n)
	{
		return this->timeline[n];
	}

	user* SearchUserByIndex(char* arr1,user** fbusers,int totalfbusers)
	{
		//Assuming number of users entered or given are lesser than 100
		int m = arr1[1] - 48;			//changing arr1[1] (i.e character) into integer m
		if (arr1[2] != '\0')
		{
			int m2 = arr1[2] - 48;
			m = m * 10 + m2;			//Adding 2nd character into first one
		}

	

		for (int i = 0; i < totalfbusers; i++)
		{
			int n = fbusers[i]->returnid();
			if (m == n)
			{
				return fbusers[i];
			}

		}
		return 0;
	}

	int Getnofreinds()
	{
		return nooffriends;
	}

	int getnooflikedpaes()
	{
		return nooflikedpages;
	}

	page** getlikedpages()
	{
		return likedpages;
	}

	void PRINTUSER(user* u)
	{
		u->PrintUser();
		cout << "\t";
		u->PrintName();
		cout << endl;
	}

	void SeeMemory(user** fbusers,page** fbpages,int totalfbusers,int totalfbpages)
	{
		Date currenttdate = Date::CurrentDate;
		for (int i = 0; i < noofposts; i++)
		{
			Date cdate = timeline[i]->getDate();
			if (currenttdate.getyear() - cdate.getyear() > 1 && cdate.getday() == currenttdate.getday()&& cdate.getmonth() == currenttdate.getmonth())			// A memory is atleast an year ago
			{

				cout << "\n\n";
				cout << "On this Day \n";
				cout << currenttdate.getyear() - cdate.getyear() << " Years ago \n\n";
				timeline[i]->ViewPost(fbusers, fbpages, totalfbusers, totalfbpages);

			}
		}
	}

	int getnofposts()
	{
		return noofposts;
	}

	void Readuserfromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		this->id = Helper::GetStringFromBuffer(temp);

		fin >> temp;
		this->fsname = Helper::GetStringFromBuffer(temp);

		fin >> temp;
		this->lsname = Helper::GetStringFromBuffer(temp);
	}

	void Likepage(const int& ctr, page* p, bool& allocation)
	{
		if (allocation == 0)
		{

			likedpages = new page * [10];
			allocation = true;
		}
		this->likedpages[ctr] = p;
		nooflikedpages++;
	}

	int returnid()
	{
		int m = id[1] - 48;
		if (id[2] != '\0')
			m = m * 10 + id[2] - 48;

		return m;
	}

	void Addfriend(const int& ctr, user* u)
	{
		freindlist[ctr] = u;
		nooffriends++;
	}

	void Allocatefriendlist()
	{
		this->freindlist = new user * [10];
	}

	void PrintName()
	{
		int size = 0;
		size = Helper::Stringlength(fsname);
		for (int i = 0; i < size; i++)
		{
			cout << fsname[i];
		}
		cout << " ";

		size = Helper::Stringlength(lsname);
		for (int i = 0; i < size; i++)
		{
			cout << lsname[i];
		}
	}

	void Printfriends()
	{
		for (int i = 0; i < 10; i++)
		{
			if (this->freindlist[i] != 0)
			{
				freindlist[i]->PrintUser();
				cout << "   ";
				this->freindlist[i]->PrintName();
				cout << endl;
			}
			else
				break;

		}




	}

	void PrintUser()
	{
		int size = Helper::Stringlength(this->id);
		for (int i = 0; i < size; i++)
		{
			cout << id[i];
		}
	}

	void PrintLikedPages()
	{
		cout << "\n";
		for (int i = 0; i < 10; i++)
		{
			if (likedpages[i] != 0)
				this->likedpages[i]->PrintPage();
			else
				break;
		}
	}

	void ViewTimeline(user** fbusers, page** fbpages, int totalfbusers, int totalfbpages)
	{
		for (int i = 0; i < noofposts; i++)
		{
			timeline[i]->ViewPost(fbusers,fbpages,totalfbusers,totalfbpages);
		}
	}


	void PlacefriendlistNull(int ctr)
	{
		if (freindlist[ctr] != 0)
			this->freindlist[ctr] = 0;
	}

	void PlacelikepagesNull(int ctr)
	{
		if (likedpages[ctr] != 0)
			this->likedpages[ctr] = 0;
	}

	void printDetailedView(Date cdate)
	{
		for (int i = 0; i < noofposts; i++)
		{
			int currentDay = cdate.getday();
			int postedDay = timeline[i]->postedDay();
			if (currentDay - postedDay == 1 || currentDay - postedDay == 0)
				timeline[i]->PrintDetailedView();
		}
	}

	void addPost(Post*& rhs)
	{

		if (noofposts < 10)
		{
			for (int i = 0; i < 10; i++)
			{
				if (timeline[i] == NULL)
				{
					timeline[i] = new Post;
					timeline[i]->setID(rhs->getID());
					timeline[i]->setDescription(rhs->getDescription());
					timeline[i]->setDate(rhs->getDate());
					//timeline[i]->setCommentCount(rhs->getCommentCount());
					//timeline[i]->setComment(rhs->getComment());
					timeline[i]->setSharedby(rhs->getSharedby());
					timeline[i]->setLikeCount(rhs->getLikecount());
					timeline[i]->setLikedUser(rhs->getLiked());
					delete rhs;
					rhs = timeline[i];
					noofposts++;
					break;
				}
			}
		}
		else
		{
			cout << "MAXIMUM LIMIT OF POSTS REACHED\n";
		}
	}

	char* GetId()
	{
		return this->id;
	}

	void InitializeTimeline(int noofpost)
	{

		noofposts = noofpost;
		if (timeline == NULL)
		{
			timeline = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				timeline[i] = 0;
			}
		}

	}

	void AddTimeline(Post* p, int ctr)
	{
		if (timeline != nullptr)
		{
			timeline[ctr] = p;
		}
	}

	/*void PrintPost()
	{
		for (int i = 0; i < noofposts; i++)
		{
			timeline[i]->ViewPost();
		}
	}*/

	void Setmemory(Memory* mem)
	{
		memory = mem;
	}

};

class Facebook :public object
{

private:
	page** fbpages;
	user** fbusers;
	Post** fbposts;
	Comment** fbcomments;

public:
	static int totalfbpages;
	static int totalfbusers;
	static int totalfbposts;
	static int totalfbcomments;
	static Date Currentdate;

	Facebook()
	{
		fbpages = 0;
		fbusers = 0;
		fbposts = 0;
		fbcomments = 0;
	}

	void LoadData(const char file1[], const char file2[], const char file3[], const char file4[])
	{
		this->LoadPages(file1);
		this->LoadUsers(file2);
		this->LoadComments(file4);
		this->LoadPosts(file3);
	}

	void LoadPages(const char file[])
	{
		ifstream fin;
		fin.open(file);
		if (fin.is_open())
		{
			int totalpages = 0;
			fin >> totalpages;
			totalfbpages = totalpages;
			fbpages = new page * [totalpages];
			for (int i = 0; i < totalpages; i++)
			{
				fbpages[i] = new page;
				fbpages[i]->Readpagefromfile(fin);
			}
			fin.close();
		}
		else
			cout << "\nFile doesn't exists\n";
	}

	void LoadUsers(const char file[])
	{
		ifstream fin;
		fin.open(file);
		if (fin.is_open())
		{

			int totalusers = 0;
			fin >> totalusers;
			totalfbusers = totalusers;
			fbusers = new user * [totalusers];

			int ctr = 0;

			//Allocation of temp3d
			char*** tempfriendlist = new char** [totalusers];
			for (int i = 0; i < totalusers; i++)
			{
				tempfriendlist[i] = new char* [10];
				for (int j = 0; j < 10; j++)
					tempfriendlist[i][j] = new char[10];
			}

			char temp[50];
			for (int i = 0; i < totalusers; i++)
			{
				fbusers[i] = new user;
				fbusers[i]->Readuserfromfile(fin);

				int k = 0;
				while (k < 11)
				{
					fin >> temp;
					if (temp[0] != '-')
					{
						tempfriendlist[i][k] = Helper::GetStringFromBuffer(temp);   //storing id of freinds in temp array
						k++;
					}
					else
					{
						tempfriendlist[i][k] = 0;   //AT THE END
						k++;
						break;
					}
				}


				ctr = 0;
				k = 0;
				page* p = 0;
				bool allocation = false;

				while (k < 11)
				{
					fin >> temp;
					if (temp[0] != '-')
					{
						p = this->SearchPageByIndex(temp);
						fbusers[i]->Likepage(ctr, p, allocation);		//ADD LIKED PAGES
						ctr++;

					}
					else
					{
						if (ctr != 0)
							fbusers[i]->PlacelikepagesNull(ctr);		//PLACING NULL ON THE LAST SPACE
						if (ctr == 0)
						{

						}
						break;
					}
				}



			}

			for (int i = 0; i < totalfbusers; i++)
			{
				fbusers[i]->Allocatefriendlist();				//ALLOCATE FREIND LIST
			}

			for (int i = 0; i < totalfbusers; i++)
			{

				char* arr = 0;
				user* u = 0;
				int ctr1 = 0;
				for (int j = 0; j < 10; j++)
				{
					if (tempfriendlist[i][j] != 0)
					{
						arr = tempfriendlist[i][j];		//store character array of user
						u = SearchUserByIndex(arr);		// gives user pointer
						fbusers[i]->Addfriend(ctr1, u);	// stores them in friend list of user 
						ctr1++;
					}
					else
					{
						if (ctr1 != 0)
							fbusers[i]->PlacefriendlistNull(ctr1);	//places null at the end
						break;
					}
				}

			}
			fin.close();


			//Deallocation of 3d temp array
			for (int i = 0; i < totalfbusers; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					delete[] tempfriendlist[i][j];
				}
			}

			for (int i = 0; i < totalfbusers; i++)
			{
				delete[] tempfriendlist[i];
			}

			delete[] tempfriendlist;

		}
		else
			cout << "\nFile doesn't exists\n";

	}

	void LoadComments(const char file[])
	{
		ifstream fin;
		fin.open(file);
		if (fin.is_open())
		{
			fin >> totalfbcomments;
			fbcomments = new Comment * [totalfbcomments];
			for (int i = 0; i <= totalfbcomments; i++)
			{
				fbcomments[i] = new Comment;
				fbcomments[i]->ReadDatafromfile(fin);
			}


		}
	}

	void LoadPosts(const char file[])
	{
		ifstream fin;
		fin.open(file);
		if (fin.is_open())
		{
			fin >> totalfbposts;
			fbposts = new Post * [totalfbposts];
			for (int i = 0; i < totalfbposts; i++)
			{
				fbposts[i] = new Post;
				fbposts[i]->ReadDatafromFile(fin);
				char* sharedby;
				char temp[80];
				fin >> temp;
				sharedby = Helper::GetStringFromBuffer(temp);
				fbposts[i]->SharePost(sharedby);

				char** temp2d = new char* [10];

				fin >> temp;

				int likedusers = 0;

				while (temp[0] != '-')				//TEMPORARY ARRAY OF LIKED USERS
				{
					temp2d[likedusers] = new char[4];
					temp2d[likedusers] = Helper::GetStringFromBuffer(temp);
					likedusers++;
					fin >> temp;
				}

				bool like = true;
				int ctr = 0;
				fbposts[i]->AllocateLikedbyLst(likedusers); // ALLOCATES EVERY USER 
				for (int a = 0; a < likedusers; a++)
				{
					fbposts[i]->LikePost(temp2d[a], ctr);  //ADD LIKEDBY ID
					ctr++;
					like = false;
				}

				if (like)
				{
					fbposts[i]->Addnullonlikepost();   //IF THERE'S NO LIKED BY THEN IT PLACES NULL
				}


				//DEALLOCATION OF TEMPORARY ARRAY
				for (int a = 0; a < likedusers; a++)
				{
					delete[] temp2d[a];
				}

				delete[] temp2d;
			}

			//MAKING TIMELINE

			//It calculates the number of posts a user have done
			for (int i = 0; i < totalfbposts; i++)
			{
				object* userwhoposted;
				userwhoposted = fbposts[i]->getSharedby();
				int postsuserhavedone = 0;

				for (int j = 0; j < totalfbposts; j++)
				{
					object* usersofposts = fbposts[j]->getSharedby();
					if (Helper::CompareStrings(userwhoposted->getID(), usersofposts->getID()))
						postsuserhavedone++;
				}


				char* id = userwhoposted->getID();
				if (id[0] == 'u')
				{
					user* cuser = SearchUserByIndex(id);
					cuser->InitializeTimeline(postsuserhavedone);    //Initializes timeline according to the posts
					int ctr = 0;
					for (int j = 0; j < totalfbposts; j++)
					{

						object* usersofposts = fbposts[j]->getSharedby();
						if (Helper::CompareStrings(userwhoposted->getID(), usersofposts->getID()))
						{
							cuser->AddTimeline(fbposts[j], ctr);		//Adds post on the respective ctr
							ctr++;
						}
					}
				}
				else
				{
					page* cpage = SearchPageByIndex(id);
					cpage->InitializeTimeline(postsuserhavedone);			//initializes timeline to 10 posts
					int ctr = 0;
					for (int j = 0; j < totalfbposts; j++)
					{
						object* usersofposts = fbposts[j]->getSharedby();
						if (Helper::CompareStrings(userwhoposted->getID(), usersofposts->getID()))
						{
							cpage->AddTimeline(fbposts[j], ctr);			//Adds post on ctr
							ctr++;

						}
					}
				}
			}
			int ctr = 0;
			//Adding Comments to posts
			for (int i = 0; i < totalfbposts; i++)
			{
				ctr = 0;
				for (int j = 0; j < totalfbcomments; j++)
				{
					if (Helper::CompareStrings(fbposts[i]->GETID(), fbcomments[j]->getpostid()))
					{
						fbposts[i]->Addcomment(fbcomments[j], ctr);
						ctr++;
					}
				}
			}


		}

	}

	void RUN()
	{
		SetDate();

		char arr[10] = "u7";

		user* cuser = SetCurrentUser(arr);  	//if user is not already present then cuser will be null

		Seefreindlist(cuser);

		SeeLikedPages(cuser);

	//	ViewHomepage(cuser);

		ViewTimeline(cuser);

		char arr2[10] = "post5";

		ViewLikedby(arr2);

		likeAPost(cuser->GetId());

		SeeMemories(cuser);

		Sharememory(cuser);

		PrintMemory(cuser);

		char arr3[5] = "p1";
		
		ViewPage(arr3);

		CommentPost(cuser);
	}

	void SetDate()
	{
		cout << "\n------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                Set Date to (15,14,2015)\n";
		cout << "------------------------------------------------------------------------------------------------------------\n\n\n";

		Currentdate.SetDate(15, 11, 2017);
	}

	void SeeLikedPages(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Liked Pages\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cuser->PrintName();
		cout << " Liked Pages\n";
		cuser->PrintLikedPages();
	}

	void Seefreindlist(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Friend List\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cuser->PrintName();
		cout << " Friend List\n";
		cuser->Printfriends();
	}

	void CommentPost(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                Post Comment(post4,Good Luck For your result)\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";

		char pid[7] = "post4";
		char text[100] = "Good Luck For your result";

		Post* p = SearchPostByPostid(pid);

		p->Addnewcomment(cuser, text, totalfbcomments);

		//p->ViewPost(fbusers, fbpages, totalfbusers, totalfbpages);

	}

	void PrintMemory(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Timeline \n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << "\n\t";
		cuser->PrintName();
		cout << "\t Timeline\n\n";

		Memory* mem;
		mem = cuser->GetMemory();
		if (mem != 0)
		{
			mem->PrintMemory(cuser, mem);
		}

		cuser->ViewTimeline(fbusers,fbpages,totalfbusers,totalfbpages);
		
	}

	void PrintPostComments(char* ID)
	{
		char* temp = 0;
		int arr[10] = { 0 };
		SearchCommentbyid(ID, arr);
		int index = 0;
		for (int i = 0; arr[i] != -1; i++)
		{
			temp = fbcomments[arr[i]]->getCommentator()->getID();
			if (temp[0] == 'u')
			{
				index = SearchUserbyID(temp);
				cout << "\t\t";
				fbusers[index]->PrintName();
				cout << " wrote \"";
				fbcomments[arr[i]]->PrintCommentofpost(ID);
				cout << "\"" << endl;
			}
			else
			{
				index = SearchPageByID(temp);
				cout << "\t\t";
				fbpages[index]->PrintName();
				cout << " wrote \"";
				fbcomments[arr[i]]->PrintCommentofpost(ID);
				cout << "\"" << endl;
			}
		}
	}

	 page* SearchPageByIndex(char* arr1)
	{
		int m = arr1[1] - 48;
		if (arr1[2] != '\0')
		{
			int m2 = arr1[2] - 48;
			m = m * 10 + m2;
		}
		for (int i = 0; i < totalfbpages; i++)
		{
			int n = fbpages[i]->returnid();
			if (m == n)
			{
				return fbpages[i];
			}
		}
		return 0;
	}

	 user* SearchUserByIndex(char* arr1)
	{
		//Assuming number of users entered or given are lesser than 100
		int m = arr1[1] - 48;			//changing arr1[1] (i.e character) into integer m
		if (arr1[2] != '\0')
		{
			int m2 = arr1[2] - 48;
			m = m * 10 + m2;			//Adding 2nd character into first one
		}

		for (int i = 0; i < totalfbusers; i++)
		{
			int n = fbusers[i]->returnid();
			if (m == n)
			{
				return fbusers[i];
			}

		}
		return 0;
	}

	Post* SearchPostByPostid(char* arr1)
	{
		for (int i = 0; i < totalfbposts; i++)
		{
			if (Helper::CompareStrings(fbposts[i]->GETID(), arr1))
			{
				return fbposts[i];
			}

		}

		return 0;
	}

	int SearchPageByID(char* arr1)
	{
		for (int i = 0; i < totalfbpages; i++)
		{
			if (Helper::CompareStrings(arr1, fbpages[i]->getidofpage()))
				return i;
		}
		return -1;
	}

	int SearchUserbyID(const char* arr)
	{
		char* temp = 0;
		bool check = true;
		for (int i = 0; i < totalfbusers; i++)
		{
			temp = fbusers[i]->GetId();
			for (int k = 0; arr[k] != '\0'; k++)
				if (temp[k] == arr[k])
					check = true;
				else {
					check = false;
					break;
				}
			if (check == true)         //if check remained true i.e user is found,then index is returned
				return i;
		}
		return -1;                     //if user is not found,-1 is returned
	}

	int Searchpostbyid(char* id)
	{
		bool flag = true;
		char* temp = 0;
		int i = 0;
		for (int k = 0; k < totalfbposts; k++)
		{
			i = 0;
			temp = fbposts[k]->GETID();
			for (; id[i] != '\0'; i++)
			{
				if (temp[i] == id[i])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				return k;
			}
		}
		return -1;
	}

	void SearchCommentbyid(char* id, int arr[])
	{
		bool flag = true;
		char* temp = 0;
		int i = 0;
		int c = 0;
		for (int k = 0; k <= totalfbcomments; k++)
		{
			i = 0;
			temp = fbcomments[k]->getpostid();
			for (; id[i] != '\0'; i++)
			{
				if (temp[i] == id[i])
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				arr[c] = k;
				c++;
			}
		}
		arr[c] = -1;
	}

	user* SetCurrentUser(char* arr)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << "Command:                Set current user 'u7'\n";
		cout << "------------------------------------------------------------------------------------------------------------\n\n";

		user* cuser = new user;
		cuser = SearchUserByIndex(arr);

		cuser->PrintName();
		cout << "\t has been succesfully set as Current user\n";

		return cuser;
	}

	void Sharememory(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                Share Memory(post10, “Never thought I will be specialist in this field…”) \n";
		cout << "------------------------------------------------------------------------------------------------------------\n";

		char post[7] = "post10";
		char text[100] = "Never thought I will be specialist in this field.";

		Post* p = SearchPostByPostid(post);
		Memory* mem=new Memory;
		//object* obj = cuser->GetId();
		mem->ShareMemory(p, text,cuser);
		cuser->Setmemory(mem);
	}

	void SeeMemories(user* cuser)
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                See Memories \n";
		cout << "------------------------------------------------------------------------------------------------------------\n";


		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.";

		cuser->SeeMemory(fbusers,fbpages,totalfbusers,totalfbposts);

	}

	void ViewPage(char* id)
	{
		cout << "\n\n------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Page (p1)\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";

		Date cdate;
		page* p = SearchPageByIndex(id);

	
		if (p != 0)
		{
			p->PrintName();
			p->printdetailedveiw(fbusers, fbpages, totalfbusers, totalfbpages);
			
		}
		else
			cout << "Page not Found!";
	}

	void ViewTimeline(user* cuser)
	{

		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Timeline \n";
		cout << "------------------------------------------------------------------------------------------------------------\n";

		cuser->PrintName();
		cout << "\t Timeline\n";
		cuser->ViewTimeline(fbusers,fbpages,totalfbusers,totalfbpages);
		

	}

	void likeAPost(char* cuser)
	{

		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                Like Post (post5)\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";


		char temp[10] = "post5";
		int index = Searchpostbyid(temp);
		if (index != -1)
		{
			if (fbposts[index]->getLikecount() < 10)
			{
				fbposts[index]->LikePost(cuser);                                 //call to like post by current user
			}
			else
				cout << "Oops... It seems like post has already reached maximum like limit." << endl;
		}
		else
			cout << "No post found with this name." << endl;


		if (index != -1)
			ViewLikedby(temp);                        //after liking the post, the liked list is again printed by this function call
		else
			cout << "Post Not found.";

	}

	void ViewLikedby(char* arr1)
	{

		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Liked List (post5) \n";
		cout << "------------------------------------------------------------------------------------------------------------\n";


		int size1 = Helper::Stringlength(arr1);
		int size2 = 0;
		Post* cpost = new Post;
		bool Postavailable = false;
		int ctr = 0;
		for (int i = 0; i < totalfbposts; i++)
		{

			char* arr2 = fbposts[i]->GETID();
			size2 = Helper::Stringlength(arr2);

			if (size1 == size2 && size1 == 5)
			{
				if (arr1[4] == arr2[4])
					cpost = fbposts[i];
			}
			else if (size1 == 6 && size1 == size2)
				if (arr1[5] == arr2[5] && arr1[4] == arr2[4])
					cpost = fbposts[i];
				else
					cpost = 0;

		}

		cpost->veiwLikedBy(fbusers,fbpages,totalfbusers,totalfbpages);


		cout << endl;



	}

	void ViewHomepage(user* cuser)
	{

		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << " Command:                View Home\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cuser->PrintName();
		cout << "  -- Home Page";


		user** freinds;
		freinds = cuser->Getfreinds();
		int ctr = 0;
		int nofreinds = cuser->Getnofreinds();
		Date cday;
		for (int i = 0; i < nofreinds; i++)
		{
			ctr = 0;
			cout << endl;
			char* idoffreind = freinds[i]->GetId();
			for (int j = 0; j < totalfbposts; j++)
			{
				char* useridofpost = fbposts[j]->getSharedby()->getID();
				if (Helper::CompareStrings(idoffreind, useridofpost))
				{
					cday = fbposts[j]->getDate();
					if (Currentdate.getday() - cday.getday() == 1 || cday.getday() - Currentdate.getday() == 0)
					{
						user* u = SearchUserByIndex(fbposts[j]->getSharedby()->getID());
						u->PrintName();
//						fbposts[j]->ViewPost();
						cout << endl;
						PrintPostComments(fbposts[j]->GETID());
						//break;
					}
				}
			}
		}

		page** pages;
		pages = cuser->getlikedpages();


		int noofpages = cuser->getnooflikedpaes();

		for (int i = 0; i < noofpages; i++)
		{
			ctr = 0;
			cout << endl;
			char* idofpage = pages[i]->getidofpage();
			for (int j = 0; j < totalfbposts; j++)
			{
				char* useridofpost = fbposts[j]->getSharedby()->getID();
				if (Helper::CompareStrings(idofpage, useridofpost))
				{
					cday = fbposts[j]->getDate();
					if (Currentdate.getday() - cday.getday() == 1 || cday.getday() - Currentdate.getday() == 0)
					{
						page* p = SearchPageByIndex(fbposts[j]->getSharedby()->getID());
						p->PrintName();
//						fbposts[j]->ViewPost();
						cout << endl;
						PrintPostComments(fbposts[j]->GETID());
					}
				}
			}
		}

	}

	static int getCurrentDay()
	{
		return Currentdate.getday();
	}


	~Facebook()
	{
		/*Deallocation<page>(fbpages,totalfbpages);
		Deallocation<user>(fbusers,totalfbusers);*/

		if (fbpages != 0)				//checks whether fbpages is not null
		{
			for (int i = 0; i < totalfbpages; i++)
				delete this->fbpages[i];		//fbpages[i] will delete pages 

			delete[] fbpages;
		}

		if (fbusers != 0)
		{
			for (int i = 0; i < totalfbusers; i++)
				delete this->fbusers[i];

			delete[] fbusers;
		}

		
		delete[] fbposts;
		



	}
};

Date Facebook::Currentdate;
int Facebook::totalfbusers = 0;
int Facebook::totalfbpages = 0;
int Facebook::totalfbposts = 0;
int Facebook::totalfbcomments = 0;


void Post::ViewPost(user** fbusers,page** fbpages,int totalfbusers,int totalfbpages)
{
	cout << "\n\n";
	char* id = getSharedby()->getID();
	if (id[0] == 'u')
	{
		user* u;
		u = new user;
		u = u->SearchUserByIndex(id, fbusers, totalfbusers);
		u->PrintName();

	}
	else
	{
		page* p;
		p = new page;
		p = p->SearchPageByIndex(id, fbpages, totalfbpages);
		p->PrintName();
	}
	
	if (act != 0)
		act->PrintActivity();
	else
		cout << " Shared ";
	cout << "\n\" ";
	int size = Helper::Stringlength(text);
	for (int i = 0; i < size; i++)
	{
		cout << text[i];
	}
	cout << "\"  \t";

	Date cdate;
	cdate = this->getDate();
	cdate.PrintDate();
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		if (comments[i] == 0)
			break;
		else
		comments[i]->PrintComment(fbusers, fbpages, totalfbusers, totalfbpages);
	}

	cout << "\n\n";

	//	Facebook::PrintPostComments(this->GETID());

}


int main()
{

	{
		Facebook fb;
		fb.LoadData("pages.txt", "users.txt", "Posts.txt", "Comments.txt");
		fb.RUN();
	}
	return 0;
}

void Comment::PrintComment(user** fbusers,page** fbpages,int totalfbusers,int totalfbpages)
{
	object* obj = userwhocommented;
	char* id = obj->getID();
	if (id[0] == 'u')
	{
		user* u;
		u = new user;
		u = u->SearchUserByIndex(id,fbusers,totalfbusers);
		u->PrintName();
	}
	else
	{
		page* p;
		p = new page;
		p = p->SearchPageByIndex(id,fbpages,totalfbpages);
		p->PrintName();
	}
	cout << " wrote ";
	int size = Helper::Stringlength(text);
	for (int i = 0; i < size; i++)
		cout << text[i];

	cout << "\n";
}

void Post :: veiwLikedBy(user** fbusers, page** fbpages, int totalfbusers, int totalfbposts)
{
	for (int i = 0; i < likecount; i++)
	{
		char* id = likedby[i]->getID();
		if (id[0] == 'u')
		{
			user* u=new user;
			u = u->SearchUserByIndex(id, fbusers, totalfbusers);
			if (u != 0)
			{
				u->PRINTUSER(u);
			}
		}
		else
		{
			page* p=new page;
			p = p->SearchPageByIndex(id, fbpages, totalfbposts);
			p->PrintPage();
		}

	}

}

void Memory:: PrintMemory(user* cuser, Memory* mem)
{
	cout << "\n~~~~~~~~";
	cuser->PrintName();
	cout << " shared a memory~~~~~~~~~\n";

	char* text;
	text = mem->Gettext();
	cout << text;
	Date cdate = this->getDate();
	Date date = Date::CurrentDate;

	cout << date.getyear() - cdate.getyear() << " Years Ago \n";

	cuser->PrintName();
	Mem->PrintDetailedView();

}

void Post::Addnewcomment(user* cuser, char* text, int totalnoofcomments)
{
	Comment* c=new Comment;
	object* obj = new object;
	obj->setID(cuser->GetId());
	c->Makeanewcomment(totalnoofcomments, this->GETID(), text, obj);

	for (int i = 0; i < 10; i++)
	{
		if (comments[i] == 0)
		{
			comments[i] = c;
			break;
		}

	}

}