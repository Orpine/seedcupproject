else if (fk_word == INSERT)		//��һ�ؼ���Ϊinsertʱ
    {

        word = getWord(s,&tmp);
        if (stricmp(word.c_str(),"into") == 0)
        {
            word = getWord(s,&tmp);
            if (!word.empty())
            {
                fileName = word;
                word = getWord(s,&tmp);
                if (stricmp(word.c_str(),"values") == 0)		//��values�����ֵ��һ��ȡ��
                {
                    word = getWord(s,&tmp);
                    if (strcmp(word.c_str(),"(") == 0)
                    {
                        word = getWord(s,&tmp);
                        if(stricmp(word.c_str(),"select") == 0){
                            do{
                                word = getWord(s,&tmp);
                                if (!word.empty())	//
                                {
                                    Rselection.push_back(word);
                                }
                                else
                                {
                                    cout<<"error1"<<endl;
                                    return 0;
                                }
                                word = getWord(s,&tmp);
                            }while(word == ",");
                                                    //select ���﷨��ȷ
                            if (stricmp(word.c_str(), "from") != 0)
                            {
                                cout<<"Error in syntax!16"<<endl;
                                return 0;
                            }
                                        //select * from���﷨��ȷ
                            word = getWord(s,&tmp);	//����
                            if (!word.empty())
                                RfileName = word;
                            else
                            {
                                cout<<"Error in syntax!17"<<endl;
                                return 0;
                            }
                                        //��ǰ���﷨����ȷ������£���ȡ��ѯ������
                            word = getWord(s,&tmp);
                            if (word.empty()){	//������
                                Rcon_count = 0; //������
                            }
                            else if (stricmp(word.c_str(),"where") == 0)	//����where
                            {
                                word = getWord(s,&tmp);		//col1
                                if (!word.empty())
                                {
                                    Rcolumn = word;
                                    Rcon_count = 1;
                                    word = getWord(s,&tmp);
                                    if (word.empty())
                                    {
                                        Rcon_count = -1;
                                        cout<<"Error in syntax!18"<<endl;
                                        return 0;
                                    }
                                    else if (strcmp(word.c_str(),"<=") == 0)
                                        Roperater1 = "<=";
                                    else if (strcmp(word.c_str(),">=") == 0)
                                        Roperater1 = ">=";
                                    else if (strcmp(word.c_str(),"<") == 0)
                                        Roperater1 = "<";
                                    else if (strcmp(word.c_str(),">") == 0)
                                        Roperater1 = ">";
                                    else if (strcmp(word.c_str(),"==") == 0)   //�Ķ���
                                        Roperater1 = "==";
                                    else if (strcmp(word.c_str(),"~=") == 0)
                                        Roperater1 = "~=";
                                    else
                                    {
                                        Rcon_count = -1;
                                        cout<<"Error in syntax!19"<<endl;
                                        return 0;
                                    }
                                    word = getWord(s,&tmp);
                                    if (!word.empty())
                                    {
                                        if (word[0] == 39 && word[word.size()-1] == 39)
                                        word = word.substr(1,word.size()-2);
                                        Rcondition1 = word;
                                    }
                                    else
                                    {
                                        Rcon_count = -1;
                                        cout<<"Error in syntax!20"<<endl;
                                        return 0;
                                    }
                                    word = getWord(s,&tmp);
                                    if (strcmp(word.c_str(),")") != 0)
                                    {
                                        Rcon_count = -1;
                                        cout<<"Error in syntax!20"<<endl;
                                        return 0;
                                    }
                                }
                                else
                                {
                                    Rcon_count = -1;
                                    cout<<"Error in syntax!21"<<endl;
                                    return 0;
                                }
                            }
                            else
                            {
                                cout<<"error5"<<endl;
                                return 0;
                            }

                            if (con_count < 0)
                            {
                                cout<<"Error in syntax!27"<<endl;
                                return 0;
                            }

                        ShowN = 1;
                        Select1( Rselection, RfileName, Rcolumn, Rcondition1, Roperater1,ShowN);
                        unsigned int pp;
                        for(pp =0 ; pp < ReturnS.size(); pp ++)
                            insertValue.push_back(ReturnS[pp]);
                        return 1;
                    }
                    else
                    {
                        while (!word.empty() && strcmp(word.c_str(),")") != 0)
                        {
                            if (strcmp(word.c_str(),",") == 0)
                            {
                                insertValue.push_back("#");
                                word = getWord(s,&tmp);
                            }

                            else
                            {
                                insertValue.push_back(word);
                                word = getWord(s,&tmp);
                                if (strcmp(word.c_str(),",") == 0 )
                                    word = getWord(s,&tmp);
                                else if(strcmp(word.c_str(),")") == 0 )
                                    ;
                                else
                                {
                                    insertValue.clear();
                                    cout<<"error"<<endl;
                                    return 0;
                                }

                            }

                        }
                        if (strcmp(word.c_str(),")") != 0)
                        {
                            cout<<"Error in syntax!1"<<endl;
                            return 0;
                        }
                    }
                }
                    else
                    {
                        cout<<"Error in syntax!2"<<endl;
                        return 0;
                    }
                }
                else if(word == "(")
                {
                    word = getWord(s,&tmp);
                    TableCloumns.push_back(word);
                    word = getWord(s,&tmp);
                    //cout<<"error1"<<endl;
                    while(word == ",")
                    {
                        word = getWord(s,&tmp);
                        if (!word.empty())	//��Ҫminisqlֻ֧��select *�Ĳ��ҷ�ʽ����������Գ���select *����������Ϊ������
                        {
                            TableCloumns.push_back(word);
                        }
                        else
                        {
                            cout<<"error"<<endl;
                            return 0;
                        }
                        word = getWord(s,&tmp);
                    }
                    word = getWord(s,&tmp);
                    if (stricmp(word.c_str(),"values") == 0)		//��values�����ֵ��һ��ȡ��
                    {
                        word = getWord(s,&tmp);
                        if (strcmp(word.c_str(),"(") == 0)
                        {
                            word = getWord(s,&tmp);
                            while (!word.empty() && strcmp(word.c_str(),")") != 0)
                            {
                                //cout<<"11"<<endl;
                                insertValue.push_back(word);
                                word = getWord(s,&tmp);
                                if (strcmp(word.c_str(),",") == 0)
                                {
                                    word = getWord(s,&tmp);
                                    //cout<<"12"<<endl;
                                }
                            }
                            if (strcmp(word.c_str(),")") != 0)
                            {
                                cout<<"Error in syntax!1"<<endl;
                                return 0;
                            }
                        }
                        else
                        {
                            cout<<"Error in syntax!2"<<endl;
                            return 0;
                        }
                    }
                    else
                    {
                        cout<<"Error in syntax!3"<<endl;
                        return 0;
                    }
                }

                else
                {
                    cout<<"Error in syntax!4"<<endl;
                    return 0;
                }
            }
            else
            {
                cout<<"Error in syntax!5"<<endl;
                return 0;
            }
        }
    }
