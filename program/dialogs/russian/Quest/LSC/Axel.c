// торговец Аксель Йост
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Подумать только... "+GetFullName(pchar)+"! Ты вернулся с того света? Как это возможно?";
				link.l1 = "С того света не возвращаются, Аксель. Все гораздо проще - я туда и не уходил, ха-ха!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Хех, приятель, до тех пор, пока ты не уладишь конфликт с нарвалами - я не буду иметь с тобой никаких дел, ты уж извини. Мне не нужны проблемы. Ступай к Фацио - он все решит.";
				link.l1 = "Хорошо, я немедленно займусь этим вопросом.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь из моего магазина!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "О! Новое лицо! Каким ветром вас занесло на наш остров? Впрочем, это не мое дело. Давайте знакомиться: меня зовут Аксель Йост, и я хозяин этого магазина. Желаете что-нибудь купить или продать? Тогда это ко мне.";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Чем вы торгуете, Аксель?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+pchar.name+"! Рад вас видеть. Желаете что-то купить или продать?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Послушайте, Аксель, у вас нет в продаже хорошего мушкета? Не обычное солдатское ружье, а что-нибудь для прицельной стрельбы, точное и дальнобойное?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Послушайте, Аксель, к вам обращался Чад Каппер по поводу покупки бочонка виски?";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Послушайте, Аксель, вы же слышали наш разговор с этим местным дурачком. Не могу понять - что за бусинку он от меня требует? Не знаете случайно?";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Да. Займемся торговлей, Аксель!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Пока нет. Я просто зашел поздороваться с вами.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Да чем придется. Лечебные эликсиры, холодное и огнестрельное оружие, боеприпасы, кирасы, камни и минералы. Заговоренные амулеты и обереги. Прочая всевозможная мелочь, необходимая в повседневной жизни, и не очень необходимая. Мне несут все, что находят на погибших кораблях и что не нужно самим\nТак что и вы приносите, если что найдете, ну а если надо купить - я тоже всегда к вашим услугам. Но должен предупредить: корабельных товаров и продовольствия у меня в продаже нет.";
			link.l1 = "Хорошо, Аксель. Давайте посмотрим ваши товары.";
			link.l1.go = "Trade_items";
			link.l2 = "Спасибо, Аксель. Я приму к сведению. Как только мне понадобятся ваши услуги, я сразу же загляну к вам.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Да что вы все, сговорились, что ли? Вы уже третий, кто за последние две недели спрашивает меня об этом. Так вот, у меня такого оружия нет. Но несколько месяцев назад Адольф Барбье приносил мне на продажу свой охотничьий штуцер с прицелом. Великолепная вещь, скажу я вам! Это именно то, что вы ищете\nНо Барбье тогда запросил за него такую цену, будто он отлит из золота и стреляет бриллиантами. В общем, я был вынужден отказать. Так что штуцер остался у Адольфа.";
			link.l1 = "Очень интересно! И где же мне искать Барбье?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Понятия не имею. Шастает где-то по острову. Но чаще всего его можно увидеть в таверне Санчо - он любитель приложиться к кружечке рома по вечерам.";
			link.l1 = "Спасибо! Думаю, я легко его там найду. И скажи еще, Аксель, а кто еще кроме меня спрашивал про этот штуцер? Ты сказал, еще двое? Кто они, эти конкуренты?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Это Мэри Каспер и некий Марчелло по кличке Циклоп. Зачем девчонке понадобилось ружье - ума не приложу, но наша Красная Мэри - известная сумасбродка, и ей могло прийти в голову что угодно. Год назад она начала скупать порох для изготовления мин - решила глушить крабов. Слава Богу, ей это запретили\nА Марчелло хотел приобрести этот штуцер для охоты за пролетающими птицами - понимаете ли, надоела ему солонина и охота поесть свежего мяса. Я их обоих отправил искать Адольфа, а уж купили они у него это ружье, или нет - не могу знать\nДа, еще Адольфом на днях интересовался этот прохиндей, Джузеппе Фацио. Может, и он захотел купить себе этот штуцер?";
			link.l1 = "Хех, соперников у меня - хоть отбавляй. Ладно, пойду поищу этого Адольфа: глядишь, еще не сторговал свой штуцер.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Да кто же этого не знает, сударь! Он эти бусинки у всех клянчит. Он так называет крупный жемчуг. Дайте ему одну жемчужину - сразу станете лучшим другом.";
			link.l1 = "Так вот оно что! Спасибо, Аксель. Никогда бы не догадался.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Да, дружище, обращался. Но если и ты надумал купить бочонок 'Бушмилс' - то я тебе огорчу: он был единственный и Чад его уже оплатил и забрал. Могу предложить шотландский виски - он ничуть не хуже ирландского, а как на мой вкус - даже лучше.";
			link.l1 = "Может быть, позже. А что-нибудь еще у тебя Чад покупал?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Нет. Интересовался мышьяком - сказал, что у него на 'Тартарусе' расплодилось много крыс и хочет их потравить. Но мне мышьяк ни к чему - с тех пор, как я нанял этого дурачка Оле убираться в магазине, все крысы сбежали в таверну к бедняге Санчо. Чего уж так крысы не выносят Оле - я не знаю.";
			link.l1 = "Наверное, у него в роду были кошки...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ха-ха! Наверное... Так что если у кого и есть мышьяк на Острове - так это у Санчо.";
			link.l1 = "Понятно. ну что же, спасибо за информацию!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}