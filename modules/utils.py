def get_date_format(date):
    return date.split(' ')[0]

def move_or_moves(value):
    if value == 1:
        return 'move'
    return 'moves'