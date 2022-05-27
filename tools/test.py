"""A few test commands"""
import json
import click

@click.group()
def main():
    pass


@click.command()
@click.option('-m', prompt='Message', help='Input message')
@click.option('-i', help='Invert output', is_flag=True)
@click.option('-b', help='Show byte array', is_flag=True)
def show(m,i,b):
    """Converts input message to Glagolitic script and then prints it on a emulated Arduino LCD screen"""
    data = json.load(open('./data.json'))
    m = m.upper()
    l = []
    for char in m:
        if char not in data and char != " ":
            print(f'{char} is not in data.json')
            exit()
        for key in data:
            if char == key:
                if len(data[key]) > 8:
                    #append in two halfs
                    l.append(data[key][:8])
                    l.append(data[key][8:])
                else:
                    l.append(data[key])
                break
            elif char == " ":
                l.append(["00000"] * 8)
                break

    if b: print(l)

    for j in range(8):
        z = ""
        for item in l:
            z += item[j] + " "
        c = ["1","0"]
        if i:
            c = ["0","1"]

        z = z.replace(c[0], "⬛")
        z = z.replace(c[1], "⬜")

        print(z)


@click.command()
def list():
    """Lists all characters in data.json"""
    data = json.load(open('./data.json'))

    for key in data:
        print(key,":")
        l = []
        if len(data[key]) > 8:
            #append in two halfs
            l.append(data[key][:8])
            l.append(data[key][8:])
        else:
            l.append(data[key])

        for i in range(8):
            z = ""
            for item in l:
                z += item[i]
            z = z.replace("1", "⬛")
            z = z.replace("0", "⬜")
            print(z)


main.add_command(show)
main.add_command(list)


main()