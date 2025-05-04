import yaml
import os
import re

cwd = os.path.dirname(os.path.abspath(__file__))

f_db = os.path.join(cwd, 'exedb.yml')
f_dict = os.path.join(cwd, 'exedict.yml')

with open(file=f_db, mode='r', encoding='utf-8') as f:
  e_db = yaml.safe_load(f)
with open(file=f_dict, mode='r', encoding='utf-8') as f:
  e_dict = yaml.safe_load(f)

set_pattern = re.compile(r"(\d+(?:\.\d+)?)\s*\(([\d\s]+)\)")

table = { exe['name']: [] for exe in e_dict } 

for entry in e_db:

  for i, workout in enumerate(entry['workouts']):

    workout_entry = {'date': entry['date'], 'order': i, 'sets': []}

    if ('sets' not in workout):
      continue

    # 운동 타입 찾기
    type = None
    for dict_entry in e_dict:
      if workout['name'] == dict_entry['name']:
        type = dict_entry['type']
        break

    # 세트 파싱
    workout_entry['sets'] = workout_entry['sets']
    for w_str, reps_str in set_pattern.findall(workout['sets']):
      w = float(w_str)
      reps = [float(rep_str) for rep_str in reps_str.split()]
      workout_entry['sets'].extend((w, rep) for rep in reps)
    
    # 타입별로 무게 재계산
    if type == 'barbell':
      bar = 15 if 'bar' not in workout else workout['bar']
      workout_entry['sets'] = [(bar + 2 * w, r) for w, r in workout_entry['sets']]
    elif type == 'barbell-machine':
      workout_entry['sets'] = [(2 * w, r) for w, r in workout_entry['sets']]

    if 'note' in workout:
      workout_entry['note'] = workout['note']

    # 최종 워크아웃 추가
    table[workout['name']].append(workout_entry)
    
# 테이블이 제대로 만들어졌는지 확인
for key in table.keys():
  if len(table[key]) == 0:
    continue

  print(f"# {key}")

  max_ws = []
  tt_w = tt_r = 0 
  t_c = 0;

  for entry in table[key]:
    date = entry['date']
    order = entry['order']
    sets = entry['sets']

    max_w = max(sets, key=lambda t: t[0])[0]
    max_ws.append(max_w)
    max_w = int(max_w) if max_w == int(max_w) else max_w

    t_w, t_r = sum(t[0] for t in sets), sum(t[1] for t in sets)
    tt_w += t_w
    tt_r += t_r

    a_w = t_w / len(sets)
    a_r = t_r / len(sets)
    t_c += len(sets)

    print(f"\t- {date}, {len(sets)} Sets, [Max_W: {max_w}kg], [Av_W: {a_w:.2f}kg], [Av_R: {a_r:.2f}reps]")

    if 'note' in entry:
      print(f"\t  {entry['note']}")

  total_max_w = max(max_ws)
  total_max_w = int(total_max_w) if total_max_w == int(total_max_w) else total_max_w

  total_av_w = tt_w / t_c
  total_av_r = tt_r / t_c
  print(f"\t> Total [Max_W: {total_max_w}kg], [Av_W: {total_av_w:.2f}kg], [Av_R: {total_av_r:.2f}reps]") 
    


    