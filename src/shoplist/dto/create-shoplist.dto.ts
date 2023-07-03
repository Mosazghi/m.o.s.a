import { IsNotEmpty } from 'class-validator';
import { ShoplistType } from '../type/shoplist.type';

export class CreateShoplistDto {
  dropSted: number;
  @IsNotEmpty()
  komponenter: ShoplistType[];
}
