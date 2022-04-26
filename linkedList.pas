program linkedList;
type
    Pointer = ^No;
    No = record
            data: integer;
            next: Pointer;
        end;

function criarLista(head: Pointer): Pointer;
begin
    head := NIL;
end;

function criarNo(valor: integer): integer;
var novoNo: Pointer;
begin
    if(novoNo) then
    begin
        novoNo^.data := valor;
        novoNo^.next := NIL;
    end
    else then 
    begin
        writeln("erro");
    end
end;

var lista: Pointer;


begin
    criarLista(lista);
    
    writeln("ok");
end.
