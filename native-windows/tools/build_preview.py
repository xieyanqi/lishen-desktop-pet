"""Build the standalone review page from tests/preview.cpp output (stdin)."""
from pathlib import Path
import json,sys
frames=[[] for _ in range(3)]
for line in sys.stdin:
    action,index,svg=line.rstrip('\n').split('\t',2)
    frames[int(action)].append(svg)
assert all(len(f)==120 for f in frames)
page='''<!doctype html><html lang="zh-CN"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>你的小黎已上线 · 动作精修</title>
<style>*{box-sizing:border-box}body{margin:0;background:#f1f7fb;color:#344454;font-family:"Microsoft YaHei",sans-serif;min-height:100vh;display:grid;place-items:center}.wrap{width:min(760px,94vw);padding:24px}h1{font-size:26px;margin:0 0 10px}p{line-height:1.8;color:#6c8091;font-size:14px}.stage{background:#fff;border:1px solid #deebf3;border-radius:24px;text-align:center;padding:12px}svg{width:min(420px,78vw);height:420px;overflow:visible}button{border:1px solid #cbdfea;color:#47657b;background:#f5faff;border-radius:12px;padding:10px 14px;cursor:pointer;margin:4px;font:inherit;font-size:14px}button.active{background:#cce7f5;border-color:#8fbedb}.controls{margin-top:14px}#label{font-size:14px;color:#5783a2;padding:4px}.note{font-size:12px}.scrub{display:flex;gap:12px;align-items:center;font-size:13px;margin-top:12px;color:#6c8091}input{flex:1;accent-color:#82b5d1}</style>
<div class="wrap"><h1>你的小黎已上线</h1><p>打字与推眼镜 · 接触动作精修 v0.3</p><div class="stage"><svg id="pet" viewBox="0 0 320 320" role="img" aria-label="可动的黎深原型"></svg><div id="label" aria-live="polite">安静陪伴中</div></div><div class="controls"><button onclick="choose(0)">安静陪伴</button><button onclick="choose(1)">试试打字</button><button onclick="choose(2)">推推眼镜</button><button id="slow" onclick="slow=!slow">四分之一速度</button><button id="pause" onclick="paused=!paused">暂停</button></div><div class="scrub"><span>逐帧检查推眼镜</span><input id="scrub" aria-label="推眼镜动作进度" type="range" min="0" max="3.966" step="0.033" value="0"></div><p class="note">移动鼠标观察眼睛；在页面中打字观察双手。点击「推推眼镜」再慢放，或拖动进度条检查手指与镜框。此预览不读取其他程序的按键，不保存输入。人物仍为简化绘制原型，计时和计划功能尚未迁移。</p></div>
<script>const frames=FRAMES;let action=0,elapsed=0,clock=0,last=performance.now(),keyUntil=-100,autoAt=10,slow=false,paused=false,gx=0,gy=0,tx=0,ty=0,lastFrame=-1,lastAction=-1;const pet=document.getElementById('pet'),label=document.getElementById('label'),scrub=document.getElementById('scrub');
function choose(a){action=a;elapsed=0;paused=false;autoAt=clock+14;if(a===1)keyUntil=clock+4;}
scrub.addEventListener('input',()=>{action=2;elapsed=Number(scrub.value);paused=true;});
document.addEventListener('pointermove',e=>{const r=pet.getBoundingClientRect();tx=Math.max(-1,Math.min(1,(e.clientX-r.left-r.width/2)/200));ty=Math.max(-1,Math.min(1,(e.clientY-r.top-r.height*.42)/180));});
document.addEventListener('keydown',e=>{if(e.ctrlKey||e.altKey||e.metaKey||['Tab','Shift','Control','Alt','Meta'].includes(e.key)||e.target?.tagName==='INPUT')return;keyUntil=clock+1.4;if(action!==2){if(action!==1)elapsed=0;action=1;paused=false;}});
function tick(now){let dt=Math.max(0,Math.min(.1,(now-last)/1000));last=now;clock+=dt;if(!paused)elapsed+=dt*(slow?.25:1);
if(!paused&&action===1&&clock>keyUntil)choose(0);
if(!paused&&action===2&&elapsed>=4)choose(clock<keyUntil?1:0);
if(!paused&&action===0&&clock>autoAt)choose(2);
const frame=Math.min(119,Math.floor((elapsed%4)*30));if(frame!==lastFrame||action!==lastAction){pet.innerHTML=frames[action][frame];lastFrame=frame;lastAction=action;}
gx+=(tx-gx)*.12;gy+=(ty-gy)*.12;pet.querySelectorAll('.pupil').forEach(x=>x.setAttribute('transform',`translate(${gx*4},${gy*1.8})`));
label.textContent=action===0?'安静陪伴中':action===1?'手指与键帽同步按下':elapsed<.96?'抬手靠近镜框':elapsed<1.6?'接触镜框，向上推起':elapsed<2.4?'扶住镜框':elapsed<2.96?'镜框回稳，手指保持接触':'收手，回到键盘';
if(action===2)scrub.value=String(elapsed);
document.getElementById('slow').classList.toggle('active',slow);document.getElementById('pause').textContent=paused?'继续播放':'暂停';requestAnimationFrame(tick);}
requestAnimationFrame(tick);</script></html>'''.replace('FRAMES',json.dumps(frames,ensure_ascii=False))
Path(__file__).resolve().parents[1].joinpath('互动预览.html').write_text(page,encoding='utf-8')
