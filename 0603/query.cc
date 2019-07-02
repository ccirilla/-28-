#include "textquery.h"

class Query_base;

class Query
{
public:
    Query(const string & str);
    QueryResult eval(const TextQuery &t) const;
    string rep() const;
    friend Query operator ~(const Query &);
    friend Query operator |(const Query &,const Query &);
    friend Query operator &(const Query &,const Query &);

private:
    Query(shared_ptr<Query_base>q)
    : _q(q)
    {}
    shared_ptr<Query_base> _q;
};

class Query_base
{
    friend class Query;
protected:
    ~Query_base() = default;
    virtual QueryResult eval(const TextQuery &t) const = 0;
    virtual string rep() const = 0;
};

class BinaryQuery
:public Query_base
{
protected:
    BinaryQuery(const Query & lhs,const Query &rhs,const string & opSym)
    : _lhs(lhs)
    , _rhs(rhs)
    , _opSym(opSym)
    {}
    string rep()const {
        return "(" + _lhs.rep() + " "
                + _opSym + " " 
                + _rhs.rep() + ")" ;
    }
    Query _lhs;
    Query _rhs;
    string _opSym;
};

class WordQuery
:public Query_base
{
    friend class Query;
    WordQuery(const string & str)
    :_query_word(str)
    {}
    QueryResult eval(const TextQuery &t) const{
        return t.query(_query_word);
    }
    string rep() const{
        return _query_word;
    }
    string _query_word;
};

class NotQuery
:public Query_base
{
    NotQuery(const Query & query)
    : _query(query)
    {}
    friend Query operator ~(const Query &);
    string rep() const{
        return "~(" + _query.rep() + ")";
    }
    QueryResult eval(const TextQuery &t) const{
        auto del = _query.eval(t).getLines();
        auto ret_lines = make_shared<set<int>>();
        int i = 0;
        int sz = t.getFile()->size();
        auto beg = del->begin(),end = del->end();
        for(;i!=sz;i++)
        {
            if( beg != end && *beg == i )
                ++beg;
            else
            {
                ret_lines->insert(i);
            }
        }
        return QueryResult(rep(),ret_lines,t.getFile());
    }
    Query _query;
};

class OrQuery
:public BinaryQuery
{
    friend Query operator |(const Query &,const Query &);
    OrQuery(const Query &lhs,const Query &rhs)
    :BinaryQuery(lhs,rhs,"|")
    {}
    QueryResult eval(const TextQuery &t) const{
        auto lret = _lhs.eval(t).getLines();
        auto rret = _rhs.eval(t).getLines();
        auto ret_lines = make_shared<set<int>>(lret->begin(),lret->end());
        ret_lines->insert(rret->begin(),rret->end());
        return QueryResult(rep(),ret_lines,t.getFile());
    }
};

class AndQuery
:public BinaryQuery
{
    friend Query operator &(const Query &,const Query &);
    AndQuery(const Query &lhs,const Query &rhs)
    :BinaryQuery(lhs,rhs,"&")
    {}
    QueryResult eval(const TextQuery &t) const {
        auto lret = _lhs.eval(t).getLines();
        auto rret = _rhs.eval(t).getLines();
        auto ret_lines = make_shared<set<int>>();
        set_intersection(lret->begin(),lret->end(),rret->begin(),rret->end()
                         ,inserter(*ret_lines,ret_lines->begin()));
        return QueryResult(rep(),ret_lines,t.getFile());
    }
};


Query::Query(const string & str)
: _q(new WordQuery(str))
{
}
QueryResult Query::eval(const TextQuery &t) const{
    return _q->eval(t);
}
string Query::rep() const{
    return _q->rep();
}
Query operator ~(const Query & q){
    shared_ptr<Query_base> ptmp (new NotQuery(q));
    return Query(ptmp);
}
Query operator |(const Query &lhs,const Query &rhs){
    shared_ptr<Query_base> ptmp (new OrQuery(lhs,rhs));
    return Query(ptmp);
}
Query operator &(const Query & lhs,const Query & rhs){
    shared_ptr<Query_base> ptmp (new AndQuery(lhs,rhs));
    return Query(ptmp);
}

int main()
{
    TextQuery tq;
    tq.readFile("china_daily.txt");
    Query ret = ~(Query("is")|Query("a"))&Query("for");
    cout << ret.eval(tq);
    return 0;
}










